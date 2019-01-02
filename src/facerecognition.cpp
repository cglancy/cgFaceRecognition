/**
* Copyright 2019 Charles Glancy (charles@glancyfamily.net)
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction, including  without limitation the rights to use, copy,
* modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
* is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
* WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
* COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "facerecognition.h"

#include <map>
#include <algorithm>

#include <dlib/dnn.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace dlib;

// ----------------------------------------------------------------------------------------

// The next bit of code defines a ResNet network.  It's basically copied
// and pasted from the dnn_imagenet_ex.cpp example, except we replaced the loss
// layer with loss_metric and made the network somewhat smaller.  Go read the introductory
// dlib DNN examples to learn what all this stuff means.
//
// Also, the dnn_metric_learning_on_images_ex.cpp example shows how to train this network.
// The dlib_face_recognition_resnet_model_v1 model used by this example was trained using
// essentially the code shown in dnn_metric_learning_on_images_ex.cpp except the
// mini-batches were made larger (35x15 instead of 5x5), the iterations without progress
// was set to 10000, and the training dataset consisted of about 3 million images instead of
// 55.  Also, the input layer was locked to images of size 150.
template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<
    alevel0<
    alevel1<
    alevel2<
    alevel3<
    alevel4<
    max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2,
    input_rgb_image_sized<150>
    >>>>>>>>>>>>;

// ----------------------------------------------------------------------------------------

namespace cg
{
    typedef matrix<float, 0, 1> face_encoding_t;

    class FaceRecognitionPrivate
    {
    public:
        std::multimap<QString, face_encoding_t> face_encoding_map;
        frontal_face_detector detector;
        shape_predictor pose_predictor;
        anet_type face_recognition_net;

        class EncodingPair
        {
        public:
            EncodingPair(const rectangle &r, const face_encoding_t &e)
                : face_rectangle(r), face_encoding(e) {}

            rectangle face_rectangle;
            face_encoding_t face_encoding;
        };

        std::vector<EncodingPair> faceEncodings(const QString & imagePath)
        {
            std::vector<EncodingPair> pairs;

            array2d<rgb_pixel> img;
            load_image(img, imagePath.toStdString());

            std::vector<matrix<rgb_pixel>> faces;
            std::vector<rectangle> rectangles = detector(img);

            for (auto rect : rectangles)
            {
                auto shape = pose_predictor(img, rect);
                matrix<rgb_pixel> face_chip;
                extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);
                faces.push_back(std::move(face_chip));
            }

            std::vector<face_encoding_t> encodings = face_recognition_net(faces);

            for (int i = 0; i < encodings.size(); i++)
                pairs.push_back(EncodingPair(rectangles[i], encodings[i]));

            return pairs;
        }
    };

    FaceRecognition::FaceRecognition(const QString & modelDirPath)
        : d_ptr(new FaceRecognitionPrivate())
    {
        QString predictor68ModelPath = modelDirPath + "/shape_predictor_68_face_landmarks.dat";
        QString predictor5ModelPath = modelDirPath + "/shape_predictor_5_face_landmarks.dat";
        QString faceRecognitionModelPath = modelDirPath + "/dlib_face_recognition_resnet_model_v1.dat";

        deserialize(predictor5ModelPath.toStdString()) >> d_ptr->pose_predictor;
        //deserialize(predictor68ModelPath.toStdString()) >> d_ptr->pose_predictor;
        deserialize(faceRecognitionModelPath.toStdString()) >> d_ptr->face_recognition_net;

        d_ptr->detector = get_frontal_face_detector();
    }

    FaceRecognition::~FaceRecognition()
    {
    }

    void FaceRecognition::addFace(const QString &key, const QString &imagePath)
    {
        std::vector<FaceRecognitionPrivate::EncodingPair> pairs = d_ptr->faceEncodings(imagePath);
        for (auto & pair : pairs)
            d_ptr->face_encoding_map.emplace(key, pair.face_encoding);
    }

    QList<FaceRecognitionRect> FaceRecognition::recognizeFaces(const QString &imagePath, float tolerance)
    {
        QList<FaceRecognitionRect> rects;

        std::vector<FaceRecognitionPrivate::EncodingPair> pairs = d_ptr->faceEncodings(imagePath);

        for (auto & pair : pairs)
        {
            std::vector<FaceRecognitionRect> candidateRects;

            for (auto & kv : d_ptr->face_encoding_map)
            {
                float distance = length(pair.face_encoding - kv.second);
                if (distance < tolerance)
                {
                    FaceRecognitionRect rect;
                    rect.distance = distance;
                    rect.rect = QRect(pair.face_rectangle.left(), pair.face_rectangle.top(), 
                        pair.face_rectangle.width(), pair.face_rectangle.height());
                    rect.key = kv.first;
                    candidateRects.push_back(rect);
                }
            }

            if (candidateRects.size() > 0)
            {
                std::sort(candidateRects.begin(), candidateRects.end(),
                    [](const FaceRecognitionRect &a, const FaceRecognitionRect &b) -> bool
                {
                    return a.distance < b.distance;
                });

                rects.append(candidateRects.at(0));
            }
        }

        return rects;
    }

}