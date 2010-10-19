#ifndef tmat_H_
#define tmat_H_

#include <iostream>
#include <iomanip>
#include "vec.h"

// Proxy class for providing the functionality of a doubly-dimensioned array
// representation of matrices.  Each matrix class defines its operator[]
// to return an ArrayProxy.  The ArrayProxy then returns the appropriate item
// from its operator[].
template<typename T>
class ArrayProxy
{
public:
    ArrayProxy(T* data) { data_ = data; }
    ~ArrayProxy() { data_ = 0; }
    T& operator[](int index)
    {
        return data_[index];
    }
    const T& operator[](int index) const
    {
        return data_[index];
    }
private:
    T* data_;
};


// All matrix objects are represented row-centric (i.e. C/C++ style references
// to the data appear as matrix[row][column]).  When using the raw data access
// member to treat the data as a singly-dimensioned array, it must be transposed.
template<typename T>
class tmat2
{
public:
    tmat2()
    {
        setIdentity();
    }
    tmat2(const tmat2& m)
    {
        m_[0] = m.m_[0];
        m_[1] = m.m_[1];
        m_[2] = m.m_[2];
        m_[3] = m.m_[3];
    }
    ~tmat2() {}

    void setIdentity()
    {
        m_[0] = 1;
        m_[1] = 0;
        m_[2] = 0;
        m_[3] = 1;
    }

    void print() const
    {
        std::cout << "| " << m_[0] << " " << m_[1] << " |" << std::endl;
        std::cout << "| " << m_[2] << " " << m_[3] << " |" << std::endl;
    }

    operator const T*() const { return &m_[0];}

    tmat2& operator=(const tmat2& rhs)
    {
        if (this != &rhs)
        {
            m_[0] = rhs.m_[0];
            m_[1] = rhs.m_[1];
            m_[2] = rhs.m_[2];
            m_[3] = rhs.m_[3];
        }
        return *this;
    }

    tmat2& operator+=(const tmat2& rhs)
    {
        m_[0] += rhs.m_[0];
        m_[1] += rhs.m_[1];
        m_[2] += rhs.m_[2];
        m_[3] += rhs.m_[3];
        return *this;
    }

    const tmat2 operator+(const tmat2& rhs)
    {
        return tmat2(*this) += rhs;
    }

    tmat2& operator-=(const tmat2& rhs)
    {
        m_[0] -= rhs.m_[0];
        m_[1] -= rhs.m_[1];
        m_[2] -= rhs.m_[2];
        m_[3] -= rhs.m_[3];
        return *this;
    }

    const tmat2 operator-(const tmat2& rhs)
    {
        return tmat2(*this) += rhs;
    }

    tmat2& operator*=(const tmat2& rhs)
    {
        T r0c0((m_[0] * rhs.m_[0]) + (m_[1] * rhs.m_[2]));
        T r0c1((m_[0] * rhs.m_[1]) + (m_[1] * rhs.m_[3]));
        T r1c0((m_[2] * rhs.m_[0]) + (m_[3] * rhs.m_[2]));
        T r1c1((m_[2] * rhs.m_[1]) + (m_[3] * rhs.m_[3]));
        m_[0] = r0c0;
        m_[1] = r0c1;
        m_[2] = r1c0;
        m_[3] = r1c1;
        return *this;
    }

    const tmat2 operator*(const tmat2& rhs)
    {
        return tmat2(*this) *= rhs;
    }

    tmat2& operator*=(const T& rhs)
    {
        m_[0] *= rhs;
        m_[1] *= rhs;
        m_[2] *= rhs;
        m_[3] *= rhs;
        return *this;
    }

    const tmat2 operator*(const T& rhs)
    {
        return tmat2(*this) *= rhs;
    }

    tmat2& operator/=(const T& rhs)
    {
        m_[0] /= rhs;
        m_[1] /= rhs;
        m_[2] /= rhs;
        m_[3] /= rhs;
        return *this;
    }

    const tmat2 operator/(const T& rhs)
    {
        return tmat2(*this) /= rhs;
    }

    ArrayProxy<T> operator[](int index)
    {
        return ArrayProxy<T>(&m_[index * 2]);
    }
    const ArrayProxy<T> operator[](int index) const
    {
        return ArrayProxy<T>(const_cast<T*>(&m_[index * 2]));
    }

private:
    T m_[4];
};

template<typename T>
const tmat2<T> operator*(const T& lhs, const tmat2<T>& rhs)
{
    return tmat2<T>(rhs) * lhs;
}

template<typename T>
const tvec2<T> operator*(const tvec2<T>& lhs, const tmat2<T>& rhs)
{
    T x((lhs.x() * rhs[0][0]) + (lhs.y() * rhs[1][0]));
    T y((lhs.x() * rhs[0][1]) + (lhs.y() * rhs[1][1]));
    return tvec2<T>(x,y);
}

template<typename T>
const tvec2<T> operator*(const tmat2<T>& lhs, const tvec2<T>& rhs)
{
    T x((lhs[0][0] * rhs.x()) + (lhs[0][1] * rhs.y()));
    T y((lhs[1][0] * rhs.x()) + (lhs[1][1] * rhs.y()));
    return tvec2<T>(x, y);
}

template<typename T>
const tmat2<T> outer(const tvec2<T>& a, const tvec2<T>& b)
{
    tmat2<T> product;
    product[0][0] = a.x() * b.x();
    product[0][1] = a.x() * b.y();
    product[1][0] = a.y() * b.x();
    product[1][1] = a.y() * b.y();
    return product;
}

template<typename T>
class tmat3
{
public:
    tmat3()
    {
        setIdentity();
    }
    tmat3(const tmat3& m)
    {
        m_[0] = m.m_[0];
        m_[1] = m.m_[1];
        m_[2] = m.m_[2];
        m_[3] = m.m_[3];
        m_[4] = m.m_[4];
        m_[5] = m.m_[5];
        m_[6] = m.m_[6];
        m_[7] = m.m_[7];
        m_[8] = m.m_[8];
    }
    ~tmat3() {}

    void setIdentity()
    {
        m_[0] = 1;
        m_[1] = 0;
        m_[2] = 0;
        m_[3] = 0;
        m_[4] = 1;
        m_[5] = 0;
        m_[6] = 0;
        m_[7] = 0;
        m_[8] = 1;
    }

    void print() const
    {
        std::cout << "| " << m_[0] << " " << m_[1] << " " << m_[2] << " |" << std::endl;
        std::cout << "| " << m_[3] << " " << m_[4] << " " << m_[5] << " |" << std::endl;
        std::cout << "| " << m_[6] << " " << m_[7] << " " << m_[8] << " |" << std::endl;
    }

    operator const T*() const { return &m_[0];}

    tmat3& operator=(const tmat3& rhs)
    {
        if (this != &rhs)
        {
            m_[0] = rhs.m_[0];
            m_[1] = rhs.m_[1];
            m_[2] = rhs.m_[2];
            m_[3] = rhs.m_[3];
            m_[4] = rhs.m_[4];
            m_[5] = rhs.m_[5];
            m_[6] = rhs.m_[6];
            m_[7] = rhs.m_[7];
            m_[8] = rhs.m_[8];
        }
        return *this;
    }

    tmat3& operator+=(const tmat3& rhs)
    {
        m_[0] += rhs.m_[0];
        m_[1] += rhs.m_[1];
        m_[2] += rhs.m_[2];
        m_[3] += rhs.m_[3];
        m_[4] += rhs.m_[4];
        m_[5] += rhs.m_[5];
        m_[6] += rhs.m_[6];
        m_[7] += rhs.m_[7];
        m_[8] += rhs.m_[8];
        return *this;
    }

    const tmat3 operator+(const tmat3& rhs)
    {
        return tmat3(*this) += rhs;
    }

    tmat3& operator-=(const tmat3& rhs)
    {
        m_[0] -= rhs.m_[0];
        m_[1] -= rhs.m_[1];
        m_[2] -= rhs.m_[2];
        m_[3] -= rhs.m_[3];
        m_[4] -= rhs.m_[4];
        m_[5] -= rhs.m_[5];
        m_[6] -= rhs.m_[6];
        m_[7] -= rhs.m_[7];
        m_[8] -= rhs.m_[8];
        return *this;
    }

    const tmat3 operator-(const tmat3& rhs)
    {
        return tmat3(*this) -= rhs;
    }

    tmat3& operator*=(const tmat3& rhs)
    {
        T r0c0((m_[0] * rhs.m_[0]) + (m_[1] * rhs.m_[3]) + (m_[2] * rhs.m_[6]));
        T r0c1((m_[0] * rhs.m_[1]) + (m_[1] * rhs.m_[4]) + (m_[2] * rhs.m_[7]));
        T r0c2((m_[0] * rhs.m_[2]) + (m_[1] * rhs.m_[5]) + (m_[2] * rhs.m_[8]));
        T r1c0((m_[3] * rhs.m_[0]) + (m_[4] * rhs.m_[3]) + (m_[5] * rhs.m_[6]));
        T r1c1((m_[3] * rhs.m_[1]) + (m_[4] * rhs.m_[4]) + (m_[5] * rhs.m_[7]));
        T r1c2((m_[3] * rhs.m_[2]) + (m_[4] * rhs.m_[5]) + (m_[5] * rhs.m_[8]));
        T r2c0((m_[6] * rhs.m_[0]) + (m_[7] * rhs.m_[3]) + (m_[8] * rhs.m_[6]));
        T r2c1((m_[6] * rhs.m_[1]) + (m_[7] * rhs.m_[4]) + (m_[8] * rhs.m_[7]));
        T r2c2((m_[6] * rhs.m_[2]) + (m_[7] * rhs.m_[5]) + (m_[8] * rhs.m_[8]));
        m_[0] = r0c0;
        m_[1] = r0c1;
        m_[2] = r0c2;
        m_[3] = r1c0;
        m_[4] = r1c1;
        m_[5] = r1c2;
        m_[6] = r2c0;
        m_[7] = r2c1;
        m_[8] = r2c2;
        return *this;
    }

    const tmat3 operator*(const tmat3& rhs)
    {
        return tmat3(*this) *= rhs;
    }

    tmat3& operator*=(const T& rhs)
    {
        m_[0] *= rhs;
        m_[1] *= rhs;
        m_[2] *= rhs;
        m_[3] *= rhs;
        m_[4] *= rhs;
        m_[5] *= rhs;
        m_[6] *= rhs;
        m_[7] *= rhs;
        m_[8] *= rhs;
        return *this;
    }

    const tmat3 operator*(const T& rhs)
    {
        return tmat3(*this) *= rhs;
    }

    tmat3& operator/=(const T& rhs)
    {
        m_[0] /= rhs;
        m_[1] /= rhs;
        m_[2] /= rhs;
        m_[3] /= rhs;
        m_[4] /= rhs;
        m_[5] /= rhs;
        m_[6] /= rhs;
        m_[7] /= rhs;
        m_[8] /= rhs;
        return *this;
    }

    const tmat3 operator/(const T& rhs)
    {
        return tmat3(*this) /= rhs;
    }

    ArrayProxy<T> operator[](int index)
    {
        return ArrayProxy<T>(&m_[index * 3]);
    }
    const ArrayProxy<T> operator[](int index) const
    {
        return ArrayProxy<T>(const_cast<T*>(&m_[index * 3]));
    }

private:
    T m_[9];
};

template<typename T>
const tmat3<T> operator*(const T& lhs, const tmat3<T>& rhs)
{
    return tmat3<T>(rhs) * lhs;
}

template<typename T>
const tvec3<T> operator*(const tvec3<T>& lhs, const tmat3<T>& rhs)
{
    T x((lhs.x() * rhs[0][0]) + (lhs.y() * rhs[1][0]) + (lhs.z() * rhs[2][0]));
    T y((lhs.x() * rhs[0][1]) + (lhs.y() * rhs[1][1]) + (lhs.z() * rhs[2][1]));
    T z((lhs.x() * rhs[0][2]) + (lhs.y() * rhs[1][2]) + (lhs.z() * rhs[2][2]));
    return tvec3<T>(x, y, z);
}

template<typename T>
const tvec3<T> operator*(const tmat3<T>& lhs, const tvec3<T>& rhs)
{
    T x((lhs[0][0] * rhs.x()) + (lhs[0][1] * rhs.y()) + (lhs[0][2] * rhs.z()));
    T y((lhs[1][0] * rhs.x()) + (lhs[1][1] * rhs.y()) + (lhs[1][2] * rhs.z()));
    T z((lhs[2][0] * rhs.x()) + (lhs[2][1] * rhs.y()) + (lhs[2][2] * rhs.z()));
    return tvec3<T>(x, y, z);
}

template<typename T>
const tmat3<T> outer(const tvec3<T>& a, const tvec3<T>& b)
{
    tmat3<T> product;
    product[0][0] = a.x() * b.x();
    product[0][1] = a.x() * b.y();
    product[0][2] = a.x() * b.z();
    product[1][0] = a.y() * b.x();
    product[1][1] = a.y() * b.y();
    product[1][2] = a.y() * b.z();
    product[2][0] = a.z() * b.x();
    product[2][1] = a.z() * b.y();
    product[2][2] = a.z() * b.z();
    return product;
}

template<typename T>
class tmat4
{
public:
    tmat4()
    {
        setIdentity();
    }
    tmat4(const tmat4& m)
    {
        m_[0] = m.m_[0];
        m_[1] = m.m_[1];
        m_[2] = m.m_[2];
        m_[3] = m.m_[3];
        m_[4] = m.m_[4];
        m_[5] = m.m_[5];
        m_[6] = m.m_[6];
        m_[7] = m.m_[7];
        m_[8] = m.m_[8];
        m_[9] = m.m_[9];
        m_[10] = m.m_[10];
        m_[11] = m.m_[11];
        m_[12] = m.m_[12];
        m_[13] = m.m_[13];
        m_[14] = m.m_[14];
        m_[15] = m.m_[15];
    }
    ~tmat4() {}

    void setIdentity()
    {
        m_[0] = 1;
        m_[1] = 0;
        m_[2] = 0;
        m_[3] = 0;
        m_[4] = 0;
        m_[5] = 1;
        m_[6] = 0;
        m_[7] = 0;
        m_[8] = 0;
        m_[9] = 0;
        m_[10] = 1;
        m_[11] = 0;
        m_[12] = 0;
        m_[13] = 0;
        m_[14] = 0;
        m_[15] = 1;
    }

    void print() const
    {
        static const int precision(6);
        // row 0
        std::cout << "| ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[0];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[1];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[2];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[3];
        std::cout << " |" << std::endl;
        // row 1
        std::cout << "| ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[4];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[5];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[6];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[7];
        std::cout << " |" << std::endl;
        // row 2
        std::cout << "| ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[8];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[9];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[10];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[11];
        std::cout << " |" << std::endl;
        // row 3
        std::cout << "| ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[12];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[13];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[14];
        std::cout << " ";
        std::cout << std::fixed << std::showpoint << std::setprecision(precision) << m_[15];
        std::cout << " |" << std::endl;
    }

    operator const T*() const { return &m_[0];}

    tmat4& operator=(const tmat4& rhs)
    {
        if (this != &rhs)
        {
            m_[0] = rhs.m_[0];
            m_[1] = rhs.m_[1];
            m_[2] = rhs.m_[2];
            m_[3] = rhs.m_[3];
            m_[4] = rhs.m_[4];
            m_[5] = rhs.m_[5];
            m_[6] = rhs.m_[6];
            m_[7] = rhs.m_[7];
            m_[8] = rhs.m_[8];
            m_[9] = rhs.m_[9];
            m_[10] = rhs.m_[10];
            m_[11] = rhs.m_[11];
            m_[12] = rhs.m_[12];
            m_[13] = rhs.m_[13];
            m_[14] = rhs.m_[14];
            m_[15] = rhs.m_[15];
        }
        return *this;
    }

    tmat4& operator+=(const tmat4& rhs)
    {
        m_[0] += rhs.m_[0];
        m_[1] += rhs.m_[1];
        m_[2] += rhs.m_[2];
        m_[3] += rhs.m_[3];
        m_[4] += rhs.m_[4];
        m_[5] += rhs.m_[5];
        m_[6] += rhs.m_[6];
        m_[7] += rhs.m_[7];
        m_[8] += rhs.m_[8];
        m_[9] += rhs.m_[9];
        m_[10] += rhs.m_[10];
        m_[11] += rhs.m_[11];
        m_[12] += rhs.m_[12];
        m_[13] += rhs.m_[13];
        m_[14] += rhs.m_[14];
        m_[15] += rhs.m_[15];
        return *this;
    }

    const tmat4 operator+(const tmat4& rhs)
    {
        return tmat4(*this) += rhs;
    }

    tmat4& operator-=(const tmat4& rhs)
    {
        m_[0] -= rhs.m_[0];
        m_[1] -= rhs.m_[1];
        m_[2] -= rhs.m_[2];
        m_[3] -= rhs.m_[3];
        m_[4] -= rhs.m_[4];
        m_[5] -= rhs.m_[5];
        m_[6] -= rhs.m_[6];
        m_[7] -= rhs.m_[7];
        m_[8] -= rhs.m_[8];
        m_[9] -= rhs.m_[9];
        m_[10] -= rhs.m_[10];
        m_[11] -= rhs.m_[11];
        m_[12] -= rhs.m_[12];
        m_[13] -= rhs.m_[13];
        m_[14] -= rhs.m_[14];
        m_[15] -= rhs.m_[15];
        return *this;
    }

    const tmat4 operator-(const tmat4& rhs)
    {
        return tmat4(*this) -= rhs;
    }

    tmat4& operator*=(const tmat4& rhs)
    {
        T r0c0((m_[0] * rhs.m_[0]) + (m_[1] * rhs.m_[4]) + (m_[2] * rhs.m_[8]) + (m_[3] * rhs.m_[12]));
        T r0c1((m_[0] * rhs.m_[1]) + (m_[1] * rhs.m_[5]) + (m_[2] * rhs.m_[9]) + (m_[3] * rhs.m_[13]));
        T r0c2((m_[0] * rhs.m_[2]) + (m_[1] * rhs.m_[6]) + (m_[2] * rhs.m_[10]) + (m_[3] * rhs.m_[14]));
        T r0c3((m_[0] * rhs.m_[3]) + (m_[1] * rhs.m_[7]) + (m_[2] * rhs.m_[11]) + (m_[3] * rhs.m_[15]));
        T r1c0((m_[4] * rhs.m_[0]) + (m_[5] * rhs.m_[4]) + (m_[6] * rhs.m_[8]) + (m_[7] * rhs.m_[12]));
        T r1c1((m_[4] * rhs.m_[1]) + (m_[5] * rhs.m_[5]) + (m_[6] * rhs.m_[9]) + (m_[7] * rhs.m_[13]));
        T r1c2((m_[4] * rhs.m_[2]) + (m_[5] * rhs.m_[6]) + (m_[6] * rhs.m_[10]) + (m_[7] * rhs.m_[14]));
        T r1c3((m_[4] * rhs.m_[3]) + (m_[5] * rhs.m_[7]) + (m_[6] * rhs.m_[11]) + (m_[7] * rhs.m_[15]));
        T r2c0((m_[8] * rhs.m_[0]) + (m_[9] * rhs.m_[4]) + (m_[10] * rhs.m_[8]) + (m_[11] * rhs.m_[12]));
        T r2c1((m_[8] * rhs.m_[1]) + (m_[9] * rhs.m_[5]) + (m_[10] * rhs.m_[9]) + (m_[11] * rhs.m_[13]));
        T r2c2((m_[8] * rhs.m_[2]) + (m_[9] * rhs.m_[6]) + (m_[10] * rhs.m_[10]) + (m_[11] * rhs.m_[14]));
        T r2c3((m_[8] * rhs.m_[3]) + (m_[9] * rhs.m_[7]) + (m_[10] * rhs.m_[11]) + (m_[11] * rhs.m_[15]));
        T r3c0((m_[12] * rhs.m_[0]) + (m_[13] * rhs.m_[4]) + (m_[14] * rhs.m_[8]) + (m_[15] * rhs.m_[12]));
        T r3c1((m_[12] * rhs.m_[1]) + (m_[13] * rhs.m_[5]) + (m_[14] * rhs.m_[9]) + (m_[15] * rhs.m_[13]));
        T r3c2((m_[12] * rhs.m_[2]) + (m_[13] * rhs.m_[6]) + (m_[14] * rhs.m_[10]) + (m_[15] * rhs.m_[14]));
        T r3c3((m_[12] * rhs.m_[3]) + (m_[13] * rhs.m_[7]) + (m_[14] * rhs.m_[11]) + (m_[15] * rhs.m_[15]));
        m_[0] = r0c0;
        m_[1] = r0c1;
        m_[2] = r0c2;
        m_[3] = r0c3;
        m_[4] = r1c0;
        m_[5] = r1c1;
        m_[6] = r1c2;
        m_[7] = r1c3;
        m_[8] = r2c0;
        m_[9] = r2c1;
        m_[10] = r2c2;
        m_[11] = r2c3;
        m_[12] = r3c0;
        m_[13] = r3c1;
        m_[14] = r3c2;
        m_[15] = r3c3;
        return *this;
    }

    const tmat4 operator*(const tmat4& rhs)
    {
        return tmat4(*this) *= rhs;
    }

    tmat4& operator*=(const T& rhs)
    {
        m_[0] *= rhs;
        m_[1] *= rhs;
        m_[2] *= rhs;
        m_[3] *= rhs;
        m_[4] *= rhs;
        m_[5] *= rhs;
        m_[6] *= rhs;
        m_[7] *= rhs;
        m_[8] *= rhs;
        m_[9] *= rhs;
        m_[10] *= rhs;
        m_[11] *= rhs;
        m_[12] *= rhs;
        m_[13] *= rhs;
        m_[14] *= rhs;
        m_[15] *= rhs;
        return *this;
    }

    const tmat4 operator*(const T& rhs)
    {
        return tmat4(*this) *= rhs;
    }

    tmat4& operator/=(const T& rhs)
    {
        m_[0] /= rhs;
        m_[1] /= rhs;
        m_[2] /= rhs;
        m_[3] /= rhs;
        m_[4] /= rhs;
        m_[5] /= rhs;
        m_[6] /= rhs;
        m_[7] /= rhs;
        m_[8] /= rhs;
        m_[9] /= rhs;
        m_[10] /= rhs;
        m_[11] /= rhs;
        m_[12] /= rhs;
        m_[13] /= rhs;
        m_[14] /= rhs;
        m_[15] /= rhs;
        return *this;
    }

    const tmat4 operator/(const T& rhs)
    {
        return tmat4(*this) /= rhs;
    }

    ArrayProxy<T> operator[](int index)
    {
        return ArrayProxy<T>(&m_[index * 4]);
    }
    const ArrayProxy<T> operator[](int index) const
    {
        return ArrayProxy<T>(const_cast<T*>(&m_[index * 4]));
    }

private:
    T m_[16];
};

template<typename T>
const tmat4<T> operator*(const T& lhs, const tmat4<T>& rhs)
{
    return tmat4<T>(rhs) * lhs;
}

template<typename T>
const tvec4<T> operator*(const tvec4<T>& lhs, const tmat4<T>& rhs)
{
    T x((lhs.x() * rhs[0][0]) + (lhs.y() * rhs[1][0]) + (lhs.z() * rhs[2][0]) + (lhs.w() * rhs[3][0]));
    T y((lhs.x() * rhs[0][1]) + (lhs.y() * rhs[1][1]) + (lhs.z() * rhs[2][1]) + (lhs.w() * rhs[3][1]));
    T z((lhs.x() * rhs[0][2]) + (lhs.y() * rhs[1][2]) + (lhs.z() * rhs[2][2]) + (lhs.w() * rhs[3][2]));
    T w((lhs.x() * rhs[0][3]) + (lhs.y() * rhs[1][3]) + (lhs.z() * rhs[2][3]) + (lhs.w() * rhs[3][3]));
    return tvec4<T>(x, y, z, w);
}

template<typename T>
const tvec4<T> operator*(const tmat4<T>& lhs, const tvec4<T>& rhs)
{
    T x((lhs[0][0] * rhs.x()) + (lhs[0][1] * rhs.y()) + (lhs[0][2] * rhs.z()) + (lhs[0][3] * rhs.w()));
    T y((lhs[1][0] * rhs.x()) + (lhs[1][1] * rhs.y()) + (lhs[1][2] * rhs.z()) + (lhs[1][3] * rhs.w()));
    T z((lhs[2][0] * rhs.x()) + (lhs[2][1] * rhs.y()) + (lhs[2][2] * rhs.z()) + (lhs[2][3] * rhs.w()));
    T w((lhs[3][0] * rhs.x()) + (lhs[3][1] * rhs.y()) + (lhs[3][2] * rhs.z()) + (lhs[3][3] * rhs.w()));
    return tvec4<T>(x, y, z, w);
}

template<typename T>
const tmat4<T> outer(const tvec4<T>& a, const tvec4<T>& b)
{
    tmat4<T> product;
    product[0][0] = a.x() * b.x();
    product[0][1] = a.x() * b.y();
    product[0][2] = a.x() * b.z();
    product[0][3] = a.x() * b.w();
    product[1][0] = a.y() * b.x();
    product[1][1] = a.y() * b.y();
    product[1][2] = a.y() * b.z();
    product[1][3] = a.y() * b.w();
    product[2][0] = a.z() * b.x();
    product[2][1] = a.z() * b.y();
    product[2][2] = a.z() * b.z();
    product[2][3] = a.z() * b.w();
    product[3][0] = a.w() * b.x();
    product[3][1] = a.w() * b.y();
    product[3][2] = a.w() * b.z();
    product[3][3] = a.w() * b.w();
    return product;
}

//
// Convenience typedefs.  These are here to present a homogeneous view of these
// objects with respect to shader source.
//
typedef tmat2<float> mat2;
typedef tmat3<float> mat3;
typedef tmat4<float> mat4;

typedef tmat2<double> dmat2;
typedef tmat3<double> dmat3;
typedef tmat4<double> dmat4;

typedef tmat2<int> imat2;
typedef tmat3<int> imat3;
typedef tmat4<int> imat4;

typedef tmat2<unsigned int> umat2;
typedef tmat3<unsigned int> umat3;
typedef tmat4<unsigned int> umat4;

typedef tmat2<bool> bmat2;
typedef tmat3<bool> bmat3;
typedef tmat4<bool> bmat4;

namespace Mat4
{

//
// Some functions to generate transformation matrices that used to be provided
// by OpenGL.
//
mat4 translate(float x, float y, float z);
mat4 scale(float x, float y, float z);
mat4 rotate(float angle, float x, float y, float z);
mat4 frustum(float left, float right, float bottom, float top, float near, float far);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
mat4 perspective(float fovy, float aspect, float zNear, float zFar);
mat4 lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

} // namespace Mat4

#endif // MAT_H_
