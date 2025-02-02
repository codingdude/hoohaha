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

#include <algorithm>
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

inline int Vector3d::Size()
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

inline Vector4d::Vector4d(const Vector3d& xyz, float w)
    : Vector4d(xyz[0], xyz[1], xyz[2], w)
{
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

inline void Vector4d::Init(const Vector3d& xyz, float w)
{
    m_xyzw[kXIndex] = xyz[kXIndex];
    m_xyzw[kYIndex] = xyz[kYIndex];
    m_xyzw[kZIndex] = xyz[kZIndex];
    m_xyzw[kWIndex] = w;
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

inline int Vector4d::Size()
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

inline Matrix3d::Matrix3d()
    : m_axes{}
{
}

inline Matrix3d::Matrix3d(const float* raw_ptr)
{
    Init(raw_ptr);
}

inline Matrix3d::Matrix3d(float yaw, float pitch, float roll)
{
    Init(yaw, pitch, roll);
}

inline Matrix3d::Matrix3d(const Vector3d& axis, float angle)
{
    Init(axis, angle);
}

inline Matrix3d::Matrix3d(const Vector3d& x,
                          const Vector3d& y,
                          const Vector3d& z)
    : m_axes{x, y, z}
{
}

inline Matrix3d::Matrix3d(float xx, float xy, float xz,
                          float yx, float yy, float yz,
                          float zx, float zy, float zz)
    : m_axes{{xx, xy, xz},
             {yx, yy, yz},
             {zx, zy, zz}}
{

}

inline void Matrix3d::Init(const float* raw_ptr)
{
    assert(raw_ptr);
    m_axes[kXAxis].Init(raw_ptr[0], raw_ptr[1], raw_ptr[2]);
    m_axes[kYAxis].Init(raw_ptr[3], raw_ptr[4], raw_ptr[5]);
    m_axes[kZAxis].Init(raw_ptr[6], raw_ptr[7], raw_ptr[8]);
}

inline void Matrix3d::Init(float yaw, float pitch, float roll)
{
    FromEulerAngles(yaw, pitch, roll, *this);
}

inline void Matrix3d::Init(const Vector3d& axis, float angle)
{
    FromAxisAndAngle(axis, angle, *this);
}

inline void Matrix3d::Init(const Vector3d& x,
                           const Vector3d& y,
                           const Vector3d& z)
{
    m_axes[kXAxis] = x;
    m_axes[kYAxis] = y;
    m_axes[kZAxis] = z;
}

inline void Matrix3d::Init(float xx, float xy, float xz,
                           float yx, float yy, float yz,
                           float zx, float zy, float zz)
{
    m_axes[kXAxis].Init(xx, xy, xz);
    m_axes[kYAxis].Init(yx, yy, yz);
    m_axes[kZAxis].Init(zx, zy, zz);
}

inline void Matrix3d::Clear()
{
    m_axes[kXAxis].Clear();
    m_axes[kYAxis].Clear();
    m_axes[kZAxis].Clear();
}

inline void Matrix3d::Identity()
{
    m_axes[kXAxis].Init(1.f, 0.f, 0.f);
    m_axes[kYAxis].Init(0.f, 1.f, 0.f);
    m_axes[kZAxis].Init(0.f, 0.f, 1.f);
}

inline void Matrix3d::Normalize()
{
    m_axes[kXAxis].Normalize();
    m_axes[kYAxis].Normalize();
    m_axes[kZAxis].Normalize();
}

inline void Matrix3d::Inverse()
{
    MatrixInverse(*this);
}

inline void Matrix3d::Transpose()
{
    std::swap(m_axes[0][1], m_axes[1][0]);
    std::swap(m_axes[0][2], m_axes[2][0]);
    std::swap(m_axes[1][2], m_axes[2][1]);
}

inline float* Matrix3d::Data()
{
    return m_axes->Data();
}

inline const float* Matrix3d::Data() const
{
    return m_axes->Data();
}

inline int Matrix3d::Size()
{
    return kSize * Vector3d::Size();
}

inline Matrix3d Matrix3d::GetIdentity()
{
    return {1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            0.f, 0.f, 1.f};
}

inline Matrix3d Matrix3d::GetNormalized() const
{
    return {m_axes[kXAxis].GetNormalized(),
            m_axes[kYAxis].GetNormalized(),
            m_axes[kZAxis].GetNormalized()};
}

inline Matrix3d Matrix3d::GetInversed() const
{
    Matrix3d result(*this);
    MatrixInverse(result);
    return result;
}

inline Matrix3d Matrix3d::GetTransposed() const
{
    return Matrix3d(m_axes[0][0], m_axes[1][0], m_axes[2][0],
                    m_axes[0][1], m_axes[1][1], m_axes[2][1],
                    m_axes[0][2], m_axes[1][2], m_axes[2][2]);
}

inline Vector3d Matrix3d::X() const
{
    return m_axes[kXAxis];
}

inline Vector3d Matrix3d::Y() const
{
    return m_axes[kYAxis];
}

inline Vector3d Matrix3d::Z() const
{
    return m_axes[kZAxis];
}

inline Vector3d& Matrix3d::X()
{
    return m_axes[kXAxis];
}

inline Vector3d& Matrix3d::y()
{
    return m_axes[kYAxis];
}

inline Vector3d& Matrix3d::Z()
{
    return m_axes[kXAxis];
}

inline Vector3d Matrix3d::operator[](int axis) const
{
    assert(axis >= kXAxis && axis < kSize);
    return m_axes[axis];
}

inline Vector3d& Matrix3d::operator[](int axis)
{
    assert(axis >= kXAxis && axis < kSize);
    return m_axes[axis];
}

inline Matrix3d Matrix3d::operator+(const Matrix3d& rhs) const
{
    Matrix3d result;
    MatrixAdd(*this, rhs, result);
    return result;
}

inline Matrix3d Matrix3d::operator-(const Matrix3d& rhs) const
{
    Matrix3d result;
    MatrixSubtract(*this, rhs, result);
    return result;
}

inline Matrix3d Matrix3d::operator*(const Matrix3d& rhs) const
{
    Matrix3d result;
    MatrixMultiply(*this, rhs, result);
    return result;
}

inline void Matrix3d::operator*=(const Matrix3d& rhs)
{
    MatrixMultiply(*this, rhs, *this);
}

inline Matrix4d::Matrix4d()
    : m_axes{}
{
}

inline Matrix4d::Matrix4d(const float* raw_ptr)
{
    Init(raw_ptr);
}

inline Matrix4d::Matrix4d(const Matrix3d& rotation)
{
    Init(rotation);
}

inline Matrix4d::Matrix4d(const Vector3d& translation,
                          const Matrix3d& rotation,
                          const Vector3d& scale)
{
    Init(translation, rotation, scale);
}

inline Matrix4d::Matrix4d(float fov, float aspect_ratio,
                          float near_clip_plane, float far_clip_plane)
{
    Init(fov, aspect_ratio, near_clip_plane, far_clip_plane);
}

inline Matrix4d::Matrix4d(const Vector4d& x, const Vector4d& y,
                          const Vector4d& z, const Vector4d& w)
    : m_axes{x, y, z, w}
{

}

inline Matrix4d::Matrix4d(float xx, float xy, float xz, float xw,
                          float yx, float yy, float yz, float yw,
                          float zx, float zy, float zz, float zw,
                          float wx, float wy, float wz, float ww)
    : m_axes{{xx, xy, xz, xw},
             {yx, yy, yz, yw},
             {zx, zy, zz, zw},
             {wx, wy, wz, ww}}
{
}

inline void Matrix4d::Init(const float* raw_ptr)
{
    assert(raw_ptr);
    m_axes[kXAxis].Init(raw_ptr[0],  raw_ptr[1],  raw_ptr[2],  raw_ptr[3]);
    m_axes[kYAxis].Init(raw_ptr[4],  raw_ptr[5],  raw_ptr[6],  raw_ptr[7]);
    m_axes[kZAxis].Init(raw_ptr[8],  raw_ptr[9],  raw_ptr[10], raw_ptr[11]);
    m_axes[kWAxis].Init(raw_ptr[12], raw_ptr[13], raw_ptr[14], raw_ptr[15]);
}

inline void Matrix4d::Init(const Matrix3d& rotation)
{
    m_axes[kXAxis].Init(rotation[kXAxis], 0.f);
    m_axes[kYAxis].Init(rotation[kYAxis], 0.f);
    m_axes[kZAxis].Init(rotation[kZAxis], 0.f);
    m_axes[kWAxis].Init({}, 1.f);
}

inline void Matrix4d::Init(const Vector3d& translation,
                           const Matrix3d& rotation,
                           const Vector3d& scale)
{
    m_axes[kXAxis].Init(scale[0] * rotation[0][0], scale[1] *
        rotation[0][1], scale[2] * rotation[0][2], 0.f);
    m_axes[kYAxis].Init(scale[0] * rotation[1][0], scale[1] *
        rotation[1][1], scale[2] * rotation[1][2], 0.f);
    m_axes[kZAxis].Init(scale[0] * rotation[2][0], scale[1] *
        rotation[2][1], scale[2] * rotation[2][2], 0.f);
    m_axes[kWAxis].Init(translation, 1.f);
}

inline void Matrix4d::Init(float fov, float aspect_ratio,
                           float near_clip_plane, float far_clip_plane)
{
    const float tg = std::tanf(fov * .5f);

    assert(tg && aspect_ratio && near_clip_plane != far_clip_plane);

    m_axes[1][1] = 1.f / tg;
    m_axes[0][0] = m_axes[1][1] / aspect_ratio;
    m_axes[2][2] = far_clip_plane / (far_clip_plane - near_clip_plane);
    m_axes[3][2] = near_clip_plane * far_clip_plane / (near_clip_plane - far_clip_plane);
    m_axes[2][3] = 1.f;

    m_axes[0][1] = m_axes[0][2] = m_axes[0][3] = 0.f;
    m_axes[1][0] = m_axes[1][2] = m_axes[1][3] = 0.f;
    m_axes[2][0] = m_axes[2][1] = 0.f;
    m_axes[3][0] = m_axes[3][1] = m_axes[3][3] = 0.f;
}

inline void Matrix4d::Init(const Vector4d& x, const Vector4d& y,
                           const Vector4d& z, const Vector4d& w)
{
    m_axes[kXAxis] = x;
    m_axes[kYAxis] = y;
    m_axes[kZAxis] = z;
    m_axes[kWAxis] = w;
}

inline void Matrix4d::Init(float xx, float xy, float xz, float xw,
                           float yx, float yy, float yz, float yw,
                           float zx, float zy, float zz, float zw,
                           float wx, float wy, float wz, float ww)
{
    m_axes[kXAxis].Init(xx, xy, xz, xw);
    m_axes[kYAxis].Init(yx, yy, yz, yw);
    m_axes[kZAxis].Init(zx, zy, zz, zw);
    m_axes[kWAxis].Init(wx, wy, wz, ww);
}

inline void Matrix4d::Clear()
{
    m_axes[kXAxis].Clear();
    m_axes[kYAxis].Clear();
    m_axes[kZAxis].Clear();
    m_axes[kWAxis].Clear();
}

inline void Matrix4d::Identity()
{
    m_axes[kXAxis].Init(1.f, 0.f, 0.f, 0.f);
    m_axes[kYAxis].Init(0.f, 1.f, 0.f, 0.f);
    m_axes[kZAxis].Init(0.f, 0.f, 1.f, 0.f);
    m_axes[kWAxis].Init(0.f, 0.f, 0.f, 1.f);
}

inline void Matrix4d::Normalize()
{
    m_axes[kXAxis].Normalize();
    m_axes[kYAxis].Normalize();
    m_axes[kZAxis].Normalize();
    m_axes[kWAxis].Normalize();
}

inline void Matrix4d::Inverse()
{
    MatrixInverse(*this);
}

inline void Matrix4d::Transpose()
{
    std::swap(m_axes[0][1], m_axes[1][0]);
    std::swap(m_axes[0][2], m_axes[2][0]);
    std::swap(m_axes[0][3], m_axes[3][0]);
    std::swap(m_axes[1][2], m_axes[2][1]);
    std::swap(m_axes[1][3], m_axes[3][1]);
    std::swap(m_axes[2][3], m_axes[3][2]);
}

inline float* Matrix4d::Data()
{
    return m_axes->Data();
}

inline const float* Matrix4d::Data() const
{
    return m_axes->Data();
}

inline int Matrix4d::Size()
{
    return kSize * Vector4d::Size();
}

inline Matrix4d Matrix4d::GetIdentity()
{
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f};
}

inline Matrix4d Matrix4d::GetNormalized() const
{
    return {m_axes[kXAxis].GetNormalized(),
            m_axes[kYAxis].GetNormalized(),
            m_axes[kZAxis].GetNormalized(),
            m_axes[kWAxis].GetNormalized()};
}

inline Matrix4d Matrix4d::GetInversed() const
{
    Matrix4d result(*this);
    MatrixInverse(result);
    return result;
}

inline Matrix4d Matrix4d::GetTransposed() const
{
    return {m_axes[0][0], m_axes[1][0], m_axes[2][0], m_axes[3][0],
            m_axes[0][1], m_axes[1][1], m_axes[2][1], m_axes[3][1],
            m_axes[0][2], m_axes[1][2], m_axes[2][2], m_axes[3][2],
            m_axes[0][3], m_axes[1][3], m_axes[2][3], m_axes[3][3]};
}

inline Matrix3d Matrix4d::GetRotation() const
{
    return {m_axes[0][0], m_axes[0][1], m_axes[0][2],
            m_axes[1][0], m_axes[1][1], m_axes[1][2],
            m_axes[2][0], m_axes[2][1], m_axes[2][2]};
}

inline Vector3d Matrix4d::GetTranslation() const
{
    return {m_axes[kWAxis].X(),
            m_axes[kWAxis].Y(),
            m_axes[kWAxis].Z()};
}

inline Vector4d Matrix4d::X() const
{
    return m_axes[kXAxis];
}

inline Vector4d Matrix4d::Y() const
{
    return m_axes[kYAxis];
}

inline Vector4d Matrix4d::Z() const
{
    return m_axes[kZAxis];
}

inline Vector4d Matrix4d::W() const
{
    return m_axes[kWAxis];
}

inline Vector4d& Matrix4d::X()
{
    return m_axes[kXAxis];
}

inline Vector4d& Matrix4d::y()
{
    return m_axes[kYAxis];
}

inline Vector4d& Matrix4d::Z()
{
    return m_axes[kZAxis];
}

inline Vector4d& Matrix4d::W()
{
    return m_axes[kWAxis];
}

inline Vector4d Matrix4d::operator[](int axis) const
{
    assert(axis >= kXAxis && axis < kSize);
    return m_axes[axis];
}

inline Vector4d& Matrix4d::operator[](int axis)
{
    assert(axis >= kXAxis && axis < kSize);
    return m_axes[axis];
}

inline Matrix4d Matrix4d::operator+(const Matrix4d& rhs) const
{
    Matrix4d result;
    MatrixAdd(*this, rhs, result);
    return result;
}

inline Matrix4d Matrix4d::operator-(const Matrix4d& rhs) const
{
    Matrix4d result;
    MatrixSubtract(*this, rhs, result);
    return result;
}

inline Matrix4d Matrix4d::operator*(const Matrix4d& rhs) const
{
    Matrix4d result;
    MatrixMultiply(*this, rhs, result);
    return result;
}

inline void Matrix4d::operator*=(const Matrix4d& rhs)
{
    MatrixMultiply(*this, rhs, *this);
}

}
