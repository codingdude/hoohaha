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
    inline Vector3d(float* raw_ptr);
    inline Vector3d(float x, float y, float z);

    inline void Init(float* raw_ptr);
    inline void Init(float x, float y, float z);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    inline int Size() const;

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
    inline Vector4d(float* raw_ptr);
    inline Vector4d(float x, float y, float z, float w);

    inline void Init(float* raw_ptr);
    inline void Init(float x, float y, float z, float w);
    inline void Normalize();
    inline void Clear();

    inline float* Data();
    inline const float* Data() const;

    inline int Size() const;

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

}

#include "mathlib.inl"

#endif // HOOHAHA_CORE_MATHLIB_H_
