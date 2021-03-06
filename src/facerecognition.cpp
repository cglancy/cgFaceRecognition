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
#pragma warning (disable:4503)

#include "facerecognition.h"
#include "face_p.h"

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
    class FaceRecognitionPrivate
    {
    public:
        frontal_face_detector detector;
        shape_predictor pose_predictor;
        anet_type face_recognition_net;

        std::vector<matrix<rgb_pixel>> jitter_image(const matrix<rgb_pixel>& img)
        {
            // All this function does is make 100 copies of img, all slightly jittered by being
            // zoomed, rotated, and translated a little bit differently. They are also randomly
            // mirrored left to right.
            thread_local dlib::rand rnd;

            std::vector<matrix<rgb_pixel>> crops;
            for (int i = 0; i < 100; ++i)
                crops.push_back(dlib::jitter_image(img, rnd));

            return crops;
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
        delete d_ptr;
    }

    Faces FaceRecognition::faces(const QString &imagePath, const QString &id, bool jitter)
    {
        Faces faces;

        matrix<rgb_pixel> img;
        load_image(img, imagePath.toStdString());

        std::vector<rectangle> rectangles = d_ptr->detector(img);

        for (auto rect : rectangles)
        {
            auto shape = d_ptr->pose_predictor(img, rect);
            matrix<rgb_pixel> face_chip;
            extract_image_chip(img, get_face_chip_details(shape, 150, 0.25), face_chip);

            Face face(id, QByteArray());
            face.d_ptr->rectangle = rect;

            if (jitter)
                face.d_ptr->matrix = mean(mat(d_ptr->face_recognition_net(d_ptr->jitter_image(std::move(face_chip)))));
            else
                face.d_ptr->matrix = d_ptr->face_recognition_net(std::move(face_chip));

            faces.append(face);
        }

        return faces;
    }

    Faces FaceRecognition::recognizeFaces(const Faces &knownFaces, const QString &imagePath, float tolerance)
    {
        Faces recognizedFaces;

        Faces imageFaces = faces(imagePath);

        for (auto & imageFace : imageFaces)
        {
            std::vector<Face> candidateFaces;

            for (auto & knownFace : knownFaces)
            {
                float distance = length(knownFace.d_ptr->matrix - imageFace.d_ptr->matrix);
                if (distance < tolerance)
                {
                    Face face = imageFace;
                    face.d_ptr->distance = distance;
                    face.d_ptr->id = knownFace.d_ptr->id;
                    candidateFaces.push_back(face);
                }
            }

            if (candidateFaces.size() > 0)
            {
                std::sort(candidateFaces.begin(), candidateFaces.end(),
                    [](const Face &a, const Face &b) -> bool
                {
                    return a.d_ptr->distance < b.d_ptr->distance;
                });

                recognizedFaces.append(candidateFaces.at(0));
            }
            else
            {
                recognizedFaces.append(imageFace);
            }
        }

        return recognizedFaces;
    }
}
