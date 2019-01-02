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
#include "facerecognitiontest.h"
#include "facedetection.h"
#include "facerecognition.h"

#include <QTest>

using namespace cg;

FaceRecognitionTest::FaceRecognitionTest()
{
}

FaceRecognitionTest::~FaceRecognitionTest()
{
}

void FaceRecognitionTest::init()
{
    QString appDirPath = QCoreApplication::applicationDirPath();

    m_imagesDir.setPath(appDirPath + "/../../../../test/images");
    QVERIFY(m_imagesDir.exists());

    m_modelsDir.setPath(appDirPath + "/../../../../models");
    QVERIFY(m_modelsDir.exists());
}

void FaceRecognitionTest::cleanup()
{
}

void FaceRecognitionTest::testFaceDetection()
{
    QString testImagePath = m_imagesDir.absolutePath() + "/2008_004176.jpg";
    QFileInfo fileInfo(testImagePath);
    QVERIFY(fileInfo.exists());
    if (fileInfo.exists())
    {
        QList<QRect> rectList = FaceDetection::faceLocations(testImagePath);
        QCOMPARE(rectList.size(), 7);
    }
}

void FaceRecognitionTest::testFaceRecognition()
{
    QString willFerrellImagePath = m_imagesDir.absolutePath() + "/Will_Ferrell.jpg";
    QString chadSmithImagePath = m_imagesDir.absolutePath() + "/Chad_Smith.jpg";
    QString bothImagePath = m_imagesDir.absolutePath() + "/Ferrell_Smith.jpg";

    FaceRecognition faceRecognition(m_modelsDir.absolutePath());
    faceRecognition.addFace("ferrell", willFerrellImagePath);
    faceRecognition.addFace("smith", chadSmithImagePath);
    QList<FaceRecognitionRect> rects = faceRecognition.recognizeFaces(bothImagePath);
    QCOMPARE(rects.size(), 2);

    for (auto & rect : rects)
    {
        if (rect.key == "smith")
            QVERIFY(rect.rect.contains(640, 140));
        else if (rect.key == "ferrell")
            QVERIFY(rect.rect.contains(300, 115));
    }
}
