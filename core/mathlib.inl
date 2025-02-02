/*
    Hoohaha Game Engine
    Copyright (C) 2025 codingdude@gmail.com

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include <cassert>
#include <cmath>

namespace core
{

inline Vector3d::Vector3d()
    : m_xyz{}
{
}

inline Vector3d::Vector3d(const float* raw_ptr)
{
    Init(raw_ptr);
}

inline Vector3d::Vector3d(float x, float y, float z)
    : m_xyz{x, y, z}
{
}

inline void Vector3d::Init(const float* raw_ptr)
{
    m_xyz[kXIndex] = raw_ptr[kXIndex];
    m_xyz[kYIndex] = raw_ptr[kYIndex];
    m_xyz[kZIndex] = raw_ptr[kZIndex];
}

inline void Vector3d::Init(float x, float y, float z)
{
    m_xyz[kXIndex] = x;
    m_xyz[kYIndex] = y;
    m_xyz[kZIndex] = z;
}

inline void Vector3d::Normalize()
{
    if (const auto length = Length())
    {
        m_xyz[kXIndex] /= length;
        m_xyz[kYIndex] /= length;
        m_xyz[kZIndex] /= length;
    }
}

inline void Vector3d::Clear()
{
    m_xyz[kXIndex] = 0;
    m_xyz[kYIndex] = 0;
    m_xyz[kZIndex] = 0;
}

inline float* Vector3d::Data()
{
    return m_xyz;
}

inline const float* Vector3d::Data() const
{
    return m_xyz;
}

inline int Vector3d::Size() const
{
    return kSize;
}

inline float Vector3d::Length() const
{
    return std::sqrtf(X() * X() + Y() * Y() + Z() * Z());
}

inline float Vector3d::DotProduct(const Vector3d& rhs) const
{
    return(X() * rhs.X() + Y() * rhs.Y() + Z() * rhs.Z());
}

inline Vector3d Vector3d::CrossProduct(const Vector3d& rhs) const
{
    return {Y() * rhs.Z() - Z() * rhs.Y(),
            Z() * rhs.X() - X() * rhs.Z(),
            X() * rhs.Y() - Y() * rhs.X()};
}

inline Vector3d Vector3d::GetNormalized() const
{
    if (const auto length = Length())
    {
        return {m_xyz[kXIndex] / length,
                m_xyz[kYIndex] / length,
                m_xyz[kZIndex] / length};
    }

    return {};
}

inline float Vector3d::X() const
{
    return m_xyz[kXIndex];
}

inline float Vector3d::Y() const
{
    return m_xyz[kYIndex];
}

inline float Vector3d::Z() const
{
    return m_xyz[kZIndex];
}

inline float& Vector3d::X()
{
    return m_xyz[kXIndex];
}

inline float& Vector3d::Y()
{
    return m_xyz[kYIndex];
}

inline float& Vector3d::Z()
{
    return m_xyz[kZIndex];
}

inline float Vector3d::operator[](int index) const
{
    assert(index >= kXIndex && index < kSize);
    return m_xyz[index];
}

inline float& Vector3d::operator[](int index)
{
    assert(index >= kXIndex && index < kSize);
    return m_xyz[index];
}

inline bool Vector3d::operator==(const Vector3d& rhs) const
{
    return X() == rhs.X() && Y() == rhs.Y() && Z() == rhs.Z();
}

inline bool Vector3d::operator!=(const Vector3d& rhs) const
{
    return X() != rhs.X() || Y() != rhs.Y() || Z() != rhs.Z();
}

inline Vector3d Vector3d::operator+(const Vector3d& rhs) const
{
    return Vector3d(
        X() + rhs.X(),
        Y() + rhs.Y(),
        Z() + rhs.Z()
    );
}

inline Vector3d Vector3d::operator-(const Vector3d& rhs) const
{
    return Vector3d(
        X() - rhs.X(),
        Y() - rhs.Y(),
        Z() - rhs.Z()
    );
}

inline Vector3d Vector3d::operator*(const Vector3d& rhs) const
{
    return Vector3d(
        X() * rhs.X(),
        Y() * rhs.Y(),
        Z() * rhs.Z()
    );
}

inline Vector3d Vector3d::operator/(const Vector3d& rhs) const
{
    assert(rhs.X() != 0 && rhs.Y() != 0 && rhs.Z() != 0);
    return Vector3d(
        X() / rhs.X(),
        Y() / rhs.Y(),
        Z() / rhs.Z()
    );
}

inline Vector3d Vector3d::operator*(float scalar) const
{
    return Vector3d(
        X() * scalar,
        Y() * scalar,
        Z() * scalar
    );
}

inline Vector3d Vector3d::operator/(float scalar) const
{
    assert(scalar != 0);
    return Vector3d(
        X() / scalar,
        Y() / scalar,
        Z() / scalar
    );
}

inline void Vector3d::operator+=(const Vector3d& rhs)
{
    X() += rhs.X();
    Y() += rhs.Y();
    Z() += rhs.Z();
}

inline void Vector3d::operator-=(const Vector3d& rhs)
{
    X() -= rhs.X();
    Y() -= rhs.Y();
    Z() -= rhs.Z();
}

inline void Vector3d::operator*=(const Vector3d& rhs)
{
    X() *= rhs.X();
    Y() *= rhs.Y();
    Z() *= rhs.Z();
}

inline void Vector3d::operator/=(const Vector3d& rhs)
{
    assert(rhs.X() != 0 && rhs.Y() != 0 && rhs.Z() != 0);
    X() /= rhs.X();
    Y() /= rhs.Y();
    Z() /= rhs.Z();
}

inline void Vector3d::operator*=(float scalar)
{
    X() *= scalar;
    Y() *= scalar;
    Z() *= scalar;
}

inline void Vector3d::operator/=(float scalar)
{
    assert(scalar);
    X() /= scalar;
    Y() /= scalar;
    Z() /= scalar;
}

inline Vector4d::Vector4d()
    : m_xyzw{}
{
}

inline Vector4d::Vector4d(const float* raw_ptr)
{
    Init(raw_ptr);
}

inline Vector4d::Vector4d(float x, float y, float z, float w)
    : m_xyzw{x, y, z, w}
{
}

inline void Vector4d::Init(const float* raw_ptr)
{
    assert(raw_ptr);
    m_xyzw[kXIndex] = raw_ptr[kXIndex];
    m_xyzw[kYIndex] = raw_ptr[kYIndex];
    m_xyzw[kZIndex] = raw_ptr[kZIndex];
    m_xyzw[kWIndex] = raw_ptr[kWIndex];
}

inline void Vector4d::Init(float x, float y, float z, float w)
{
    m_xyzw[kXIndex] = x;
    m_xyzw[kYIndex] = y;
    m_xyzw[kZIndex] = z;
    m_xyzw[kWIndex] = w;
}

inline void Vector4d::Normalize()
{
    if (const auto length = Length())
    {
        m_xyzw[kXIndex] /= length;
        m_xyzw[kYIndex] /= length;
        m_xyzw[kZIndex] /= length;
        m_xyzw[kWIndex] /= length;
    }
}

inline void Vector4d::Clear()
{
    m_xyzw[kXIndex] = 0;
    m_xyzw[kYIndex] = 0;
    m_xyzw[kZIndex] = 0;
    m_xyzw[kWIndex] = 0;
}

inline float* Vector4d::Data()
{
    return m_xyzw;
}

inline const float* Vector4d::Data() const
{
    return m_xyzw;
}

inline int Vector4d::Size() const
{
    return kSize;
}

inline float Vector4d::Length() const
{
    return std::sqrtf(X() * X() + Y() * Y() + Z() * Z() + W() * W());
}

inline float Vector4d::DotProduct(const Vector4d& rhs) const
{
    return (X() * rhs.X() + Y() * rhs.Y() + Z() * rhs.Z() + W() * rhs.W());
}

inline Vector4d Vector4d::GetNormalized() const
{
    if (const auto length = Length())
    {
        return {m_xyzw[kXIndex] / length,
                m_xyzw[kYIndex] / length,
                m_xyzw[kZIndex] / length,
                m_xyzw[kWIndex] / length};
    }

    return {};
}

inline float Vector4d::X() const
{
    return m_xyzw[kXIndex];
}

inline float Vector4d::Y() const
{
    return m_xyzw[kYIndex];
}

inline float Vector4d::Z() const
{
    return m_xyzw[kZIndex];
}

inline float Vector4d::W() const
{
    return m_xyzw[kWIndex];
}

inline float& Vector4d::X()
{
    return m_xyzw[kXIndex];
}

inline float& Vector4d::Y()
{
    return m_xyzw[kYIndex];
}

inline float& Vector4d::Z()
{
    return m_xyzw[kZIndex];
}

inline float& Vector4d::W()
{
    return m_xyzw[kWIndex];
}

inline float Vector4d::operator[](int index) const
{
    assert(index >= kXIndex && index < kSize);
    return m_xyzw[index];
}

inline float& Vector4d::operator[](int index)
{
    assert(index >= kXIndex && index < kSize);
    return m_xyzw[index];
}

inline bool Vector4d::operator==(const Vector4d& rhs) const
{
    return X() == rhs.X() &&
           Y() == rhs.Y() &&
           Z() == rhs.Z() &&
           W() == rhs.W();
}

inline bool Vector4d::operator!=(const Vector4d& rhs) const
{
    return X() != rhs.X() ||
           Y() != rhs.Y() ||
           Z() != rhs.Z() ||
           W() != rhs.W();
}

inline Vector4d Vector4d::operator+(const Vector4d& rhs) const
{
    return {m_xyzw[kXIndex] + rhs.X(),
            m_xyzw[kYIndex] + rhs.Y(),
            m_xyzw[kZIndex] + rhs.Z(),
            m_xyzw[kWIndex] + rhs.W()};
}

inline Vector4d Vector4d::operator-(const Vector4d& rhs) const
{
    return {m_xyzw[kXIndex] - rhs.X(),
            m_xyzw[kYIndex] - rhs.Y(),
            m_xyzw[kZIndex] - rhs.Z(),
            m_xyzw[kWIndex] - rhs.W()};
}

inline Vector4d Vector4d::operator*(const Vector4d& rhs) const
{
    return {m_xyzw[kXIndex] * rhs.X(),
            m_xyzw[kYIndex] * rhs.Y(),
            m_xyzw[kZIndex] * rhs.Z(),
            m_xyzw[kWIndex] * rhs.W()};
}

inline Vector4d Vector4d::operator/(const Vector4d& rhs) const
{
    assert(rhs.X() != 0 && rhs.Y() != 0 && rhs.Z() != 0 && W() != 0);
    return {m_xyzw[kXIndex] / rhs.X(),
            m_xyzw[kYIndex] / rhs.Y(),
            m_xyzw[kZIndex] / rhs.Z(),
            m_xyzw[kWIndex] / rhs.W()};
}

inline Vector4d Vector4d::operator*(float scalar) const
{
    return {m_xyzw[kXIndex] * scalar,
            m_xyzw[kYIndex] * scalar,
            m_xyzw[kZIndex] * scalar,
            m_xyzw[kWIndex] * scalar};
}

inline Vector4d Vector4d::operator/(float scalar) const
{
    assert(scalar != 0);
    return {m_xyzw[kXIndex] / scalar,
            m_xyzw[kYIndex] / scalar,
            m_xyzw[kZIndex] / scalar,
            m_xyzw[kWIndex] / scalar};
}

inline void Vector4d::operator+=(const Vector4d& rhs)
{
    m_xyzw[kXIndex] += rhs.X();
    m_xyzw[kYIndex] += rhs.Y();
    m_xyzw[kZIndex] += rhs.Z();
    m_xyzw[kWIndex] += rhs.W();
}

inline void Vector4d::operator-=(const Vector4d& rhs)
{
    m_xyzw[kXIndex] -= rhs.X();
    m_xyzw[kYIndex] -= rhs.Y();
    m_xyzw[kZIndex] -= rhs.Z();
    m_xyzw[kWIndex] -= rhs.W();
}

inline void Vector4d::operator*=(const Vector4d& rhs)
{
    m_xyzw[kXIndex] *= rhs.X();
    m_xyzw[kYIndex] *= rhs.Y();
    m_xyzw[kZIndex] *= rhs.Z();
    m_xyzw[kWIndex] *= rhs.W();
}

inline void Vector4d::operator/=(const Vector4d& rhs)
{
    assert(rhs.X() != 0 && rhs.Y() != 0 && rhs.Z() != 0 && W() != 0);
    m_xyzw[kXIndex] /= rhs.X();
    m_xyzw[kYIndex] /= rhs.Y();
    m_xyzw[kZIndex] /= rhs.Z();
    m_xyzw[kWIndex] /= rhs.W();
}

inline void Vector4d::operator*=(float scalar)
{
    m_xyzw[kXIndex] *= scalar;
    m_xyzw[kYIndex] *= scalar;
    m_xyzw[kZIndex] *= scalar;
    m_xyzw[kWIndex] *= scalar;
}

inline void Vector4d::operator/=(float scalar)
{
    assert(scalar != 0);
    m_xyzw[kXIndex] /= scalar;
    m_xyzw[kYIndex] /= scalar;
    m_xyzw[kZIndex] /= scalar;
    m_xyzw[kWIndex] /= scalar;
}

}
