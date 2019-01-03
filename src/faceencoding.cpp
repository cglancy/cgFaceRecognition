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
#include "faceencoding.h"
#include "faceencoding_p.h"

namespace cg
{
    FaceEncoding::FaceEncoding()
        : d_ptr(new FaceEncodingPrivate())
    {
    }

    FaceEncoding::FaceEncoding(const FaceEncoding &encoding)
        : d_ptr(new FaceEncodingPrivate())
    {
        d_ptr->matrix = encoding.d_ptr->matrix;
        d_ptr->rectangle = encoding.d_ptr->rectangle;
    }

    FaceEncoding::~FaceEncoding()
    {
        delete d_ptr;
    }

    FaceEncoding & FaceEncoding::operator=(const FaceEncoding &encoding)
    {
        d_ptr->matrix = encoding.d_ptr->matrix;
        d_ptr->rectangle = encoding.d_ptr->rectangle;
        return *this;
    }
}
