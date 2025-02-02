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

#ifndef HOOHAHA_CORE_MATHLIB_H_
#define HOOHAHA_CORE_MATHLIB_H_

namespace core
{

class Vector3d final
{
public:
    inline Vector3d();
    inline Vector3d(const float* raw_ptr);
    inline Vector3d(float x, float y, float z);

    inline void Init(const float* raw_ptr);
    inline void Init(float x, float y, float z);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    static inline int Size();

    inline float Length() const;
    inline float DotProduct(const Vector3d& rhs) const;
    inline Vector3d CrossProduct(const Vector3d& rhs) const;
    inline Vector3d GetNormalized() const;

    inline float X() const;
    inline float Y() const;
    inline float Z() const;

    inline float& X();
    inline float& Y();
    inline float& Z();

    inline float operator[](int index) const;
    inline float& operator[](int index);

    inline bool operator==(const Vector3d& rhs) const;
    inline bool operator!=(const Vector3d& rhs) const;

    inline Vector3d operator+(const Vector3d& rhs) const;
    inline Vector3d operator-(const Vector3d& rhs) const;
    inline Vector3d operator*(const Vector3d& rhs) const;
    inline Vector3d operator/(const Vector3d& rhs) const;

    inline Vector3d operator*(float scalar) const;
    inline Vector3d operator/(float scalar) const;

    inline void operator+=(const Vector3d& rhs);
    inline void operator-=(const Vector3d& rhs);
    inline void operator*=(const Vector3d& rhs);
    inline void operator/=(const Vector3d& rhs);

    inline void operator*=(float scalar);
    inline void operator/=(float scalar);

private:
    enum
    {
        kXIndex = 0,
        kYIndex = 1,
        kZIndex = 2,

        kSize = 3
    };

    float m_xyz[kSize];
};

class Vector4d final
{
public:
    inline Vector4d();
    inline Vector4d(const float* raw_ptr);
    inline Vector4d(const Vector3d& xyz, float w = 0.f);
    inline Vector4d(float x, float y, float z, float w);

    inline void Init(const float* raw_ptr);
    inline void Init(const Vector3d& xyz, float w = 0.f);
    inline void Init(float x, float y, float z, float w);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    static inline int Size();

    inline float Length() const;
    inline float DotProduct(const Vector4d& rhs) const;
    inline Vector4d GetNormalized() const;

    inline float X() const;
    inline float Y() const;
    inline float Z() const;
    inline float W() const;

    inline float& X();
    inline float& Y();
    inline float& Z();
    inline float& W();

    inline float operator[](int index) const;
    inline float& operator[](int index);

    inline bool operator==(const Vector4d& rhs) const;
    inline bool operator!=(const Vector4d& rhs) const;

    inline Vector4d operator+(const Vector4d& rhs) const;
    inline Vector4d operator-(const Vector4d& rhs) const;
    inline Vector4d operator*(const Vector4d& rhs) const;
    inline Vector4d operator/(const Vector4d& rhs) const;

    inline Vector4d operator*(float scalar) const;
    inline Vector4d operator/(float scalar) const;

    inline void operator+=(const Vector4d& rhs);
    inline void operator-=(const Vector4d& rhs);
    inline void operator*=(const Vector4d& rhs);
    inline void operator/=(const Vector4d& rhs);

    inline void operator*=(float scalar);
    inline void operator/=(float scalar);

private:
    enum
    {
        kXIndex = 0,
        kYIndex = 1,
        kZIndex = 2,
        kWIndex = 3,

        kSize = 4
    };

    float m_xyzw[kSize];
};

class Matrix3d final
{
public:
    inline Matrix3d();
    inline Matrix3d(const float* raw_ptr);
    inline Matrix3d(float yaw, float pitch, float roll);
    inline Matrix3d(const Vector3d& axis, float angle);
    inline Matrix3d(const Vector3d& x, const Vector3d& y, const Vector3d& z);
    inline Matrix3d(float xx, float xy, float xz,
                    float yx, float yy, float yz,
                    float zx, float zy, float zz);

    inline void Init(const float* raw_ptr);
    inline void Init(float yaw, float pitch, float roll);
    inline void Init(const Vector3d& axis, float angle);
    inline void Init(const Vector3d& x, const Vector3d& y, const Vector3d& z);
    inline void Init(float xx, float xy, float xz,
                     float yx, float yy, float yz,
                     float zx, float zy, float zz);

    inline void Clear();
    inline void Identity();
    inline void Normalize();
    inline void Inverse();
    inline void Transpose();

    inline float* Data();
    inline const float* Data() const;

    static inline int Size();

    static inline Matrix3d GetIdentity();
    inline Matrix3d GetNormalized() const;
    inline Matrix3d GetInversed() const;
    inline Matrix3d GetTransposed() const;

    inline Vector3d X() const;
    inline Vector3d Y() const;
    inline Vector3d Z() const;

    inline Vector3d& X();
    inline Vector3d& y();
    inline Vector3d& Z();

    inline Vector3d operator[](int axis) const;
    inline Vector3d& operator[](int axis);

    inline Matrix3d operator+(const Matrix3d& rhs) const;
    inline Matrix3d operator-(const Matrix3d& rhs) const;
    inline Matrix3d operator*(const Matrix3d& rhs) const;

    inline void operator*=(const Matrix3d& rhs);

private:
    enum
    {
        kXAxis = 0,
        kYAxis = 1,
        kZAxis = 2,

        kSize = 3
    };

    Vector3d m_axes[kSize];
};

class Matrix4d final
{
public:
    inline Matrix4d();
    inline Matrix4d(const float* raw_ptr);
    inline Matrix4d(const Matrix3d& rotation);
    inline Matrix4d(const Vector3d& translation, const Matrix3d& rotation,
                    const Vector3d& scale = {1.f, 1.f, 1.f});
    inline Matrix4d(float fov, float aspect_ratio,
                    float near_clip_plane, float far_clip_plane);
    inline Matrix4d(const Vector4d& x, const Vector4d& y,
                    const Vector4d& z, const Vector4d& w);
    inline Matrix4d(float xx, float xy, float xz, float xw,
                    float yx, float yy, float yz, float yw,
                    float zx, float zy, float zz, float zw,
                    float wx, float wy, float wz, float ww);

    inline void Init(const float* raw_ptr);
    inline void Init(const Matrix3d& rotation);
    inline void Init(const Vector3d& translation, const Matrix3d& rotation,
                     const Vector3d& scale = { 1.f, 1.f, 1.f });
    inline void Init(float fov, float aspect_ratio,
                     float near_clip_plane, float far_clip_plane);
    inline void Init(const Vector4d& x, const Vector4d& y,
                     const Vector4d& z, const Vector4d& w);
    inline void Init(float xx, float xy, float xz, float xw,
                     float yx, float yy, float yz, float yw,
                     float zx, float zy, float zz, float zw,
                     float wx, float wy, float wz, float ww);

    inline void Clear();
    inline void Identity();
    inline void Normalize();
    inline void Inverse();
    inline void Transpose();

    inline float* Data();
    inline const float* Data() const;

    static inline int Size();

    static inline Matrix4d GetIdentity();
    inline Matrix4d GetNormalized() const;
    inline Matrix4d GetInversed() const;
    inline Matrix4d GetTransposed() const;
    inline Matrix3d GetRotation() const;
    inline Vector3d GetTranslation() const;

    inline Vector4d X() const;
    inline Vector4d Y() const;
    inline Vector4d Z() const;
    inline Vector4d W() const;

    inline Vector4d& X();
    inline Vector4d& y();
    inline Vector4d& Z();
    inline Vector4d& W();

    inline Vector4d operator[](int axis) const;
    inline Vector4d& operator[](int axis);

    inline Matrix4d operator+(const Matrix4d& rhs) const;
    inline Matrix4d operator-(const Matrix4d& rhs) const;
    inline Matrix4d operator*(const Matrix4d& rhs) const;

    inline void operator*=(const Matrix4d& rhs);

private:
    enum
    {
        kXAxis = 0,
        kYAxis = 1,
        kZAxis = 2,
        kWAxis = 3,

        kSize = 4
    };

    Vector4d m_axes[kSize];
};

extern void FromEulerAngles(float yaw, float pitch, float roll, Matrix3d& out);
extern void FromAxisAndAngle(const Vector3d& axis, float angle, Matrix3d& out);
extern void MatrixAdd(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out);
extern void MatrixSubtract(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out);
extern void MatrixMultiply(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out);
extern void MatrixInverse(Matrix3d& in_out);

extern void MatrixAdd(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out);
extern void MatrixSubtract(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out);
extern void MatrixMultiply(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out);
extern void MatrixInverse(Matrix4d& in_out);

extern Vector3d operator * (const Vector3d& lhs, const Matrix3d& rhs);
extern Vector4d operator * (const Vector4d& lhs, const Matrix4d& rhs);

}

#include "mathlib.inl"

#endif // HOOHAHA_CORE_MATHLIB_H_
