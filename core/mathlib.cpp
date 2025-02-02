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

#include "mathlib.h"

namespace core
{

void FromEulerAngles(float yaw, float pitch, float roll, Matrix3d& out)
{

}

void FromAxisAndAngle(const Vector3d& axis, float angle, Matrix3d& out)
{

}

void MatrixAdd(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{

}

void MatrixSubtract(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{

}

void MatrixMultiply(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{

}

void MatrixInverse(Matrix3d& in_out)
{

}

void MatrixAdd(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{

}

void MatrixSubtract(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{

}

void MatrixMultiply(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{

}

void MatrixInverse(Matrix4d& in_out)
{

}

Vector3d operator * (const Vector3d& lhs, const Matrix3d& rhs)
{
    return {};
}

Vector4d operator * (const Vector4d& lhs, const Matrix4d& rhs)
{
    return {};
}

}