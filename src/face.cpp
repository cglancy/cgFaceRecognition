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
#include "face.h"
#include "face_p.h"

namespace cg
{
    Face::Face()
        : d_ptr(new FacePrivate())
    {
    }

    Face::Face(const QString &id, const QByteArray &encoding)
        : d_ptr(new FacePrivate())
    {
        Q_UNUSED(encoding);
        d_ptr->id = id;
    }

    Face::Face(const Face &fr)
        : d_ptr(new FacePrivate())
    {
        d_ptr->matrix = fr.d_ptr->matrix;
        d_ptr->rectangle = fr.d_ptr->rectangle;
        d_ptr->id = fr.d_ptr->id;
        d_ptr->distance = fr.d_ptr->distance;
    }

    Face::~Face()
    {
        delete d_ptr;
    }

    Face & Face::operator=(const Face &fr)
    {
        d_ptr->matrix = fr.d_ptr->matrix;
        d_ptr->rectangle = fr.d_ptr->rectangle;
        d_ptr->id = fr.d_ptr->id;
        d_ptr->distance = fr.d_ptr->distance;
        return *this;
    }

    QString Face::id() const
    {
        return d_ptr->id;
    }

    QByteArray Face::encoding() const
    {
        return QByteArray();
    }

    QRect Face::rect() const
    {
        return QRect(d_ptr->rectangle.left(), d_ptr->rectangle.top(), d_ptr->rectangle.width(), d_ptr->rectangle.height());
    }

    float Face::distance() const
    {
        return d_ptr->distance;
    }
}
