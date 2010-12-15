//
// Copyright (c) 2010 Linaro
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Contributors:
//     Jesse Barker - original implementation.
//
#ifndef STACK_H_
#define STACK_H_

#include <vector>
#include "mat.h"

//
// Simple matrix stack implementation suitable for tracking OpenGL matrix
// state.  Default construction puts an identity matrix on the top of the 
// stack.
//
template<typename T>
class MatrixStack
{
public:
    MatrixStack()
    {
        theStack_.push_back(T());
    }
    MatrixStack(const T& matrix)
    {
        theStack_.push_back(matrix);
    }
    ~MatrixStack() {}

    const T& getCurrent() const { return theStack_.back(); }

    void push()
    {
        theStack_.push_back(theStack_.back());
    }
    void pop()
    {
        theStack_.pop_back();
    }
    void loadIdentity()
    {
        theStack_.back().setIdentity();
    }
    T& operator*=(const T& rhs)
    {
        T& curMatrix = theStack_.back();
        curMatrix *= rhs;
        return curMatrix;
    }
    void print() const
    {
        const T& curMatrix = theStack_.back();
        curMatrix.print();
    }
    unsigned int getDepth() const { return theStack_.size(); }
private:
    std::vector<T> theStack_;
};

class Stack4 : public MatrixStack<mat4> 
{
public:
    void translate(float x, float y, float z)
    {
        *this *= Mat4::translate(x, y, z);
    }
    void scale(float x, float y, float z)
    {
        *this *= Mat4::scale(x, y, z);
    }
    void rotate(float angle, float x, float y, float z)
    {
        *this *= Mat4::rotate(angle, x, y, z);
    }
    void frustum(float left, float right, float bottom, float top, float near, float far)
    {
        *this *= Mat4::frustum(left, right, bottom, top, near, far);
    }
    void ortho(float left, float right, float bottom, float top, float near, float far)
    {
        *this *= Mat4::ortho(left, right, bottom, top, near, far);
    }
    void perspective(float fovy, float aspect, float zNear, float zFar)
    {
        *this *= Mat4::perspective(fovy, aspect, zNear, zFar);
    }
    void lookAt(float eyeX, float eyeY, float eyeZ, 
                float centerX, float centerY, float centerZ, 
                float upX, float upY, float upZ)
    {
        *this *= Mat4::lookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    }
};

#endif // STACK_H_
