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
#ifndef CG_FACERECOGNITION_H
#define CG_FACERECOGNITION_H
#pragma once

#include "cgfacerecognition.h"
#include "faceencoding.h"

#include <QString>
#include <QList>
#include <QMap>
#include <QRect>

namespace cg
{
    class FaceRecognitionPrivate;

    class CGFACERECOGNITION_API FaceRecognitionRect
    {
    public:
        FaceRecognitionRect();

        QString key;
        QRect rect;
        float distance;
    };

    class CGFACERECOGNITION_API FaceRecognition
    {
    public:
        FaceRecognition(const QString &modelDirPath);
        ~FaceRecognition();

        FaceEncodings faceEncodings(const QString &imagePath);
        QList<FaceRecognitionRect> recognizeFaces(const QMap<QString, FaceEncoding> &knownFaces, const QString &imagePath, float tolerance = 0.6);

    private:
        FaceRecognitionPrivate *const d_ptr;
    };
}

#endif // CG_FACERECOGNITION_H