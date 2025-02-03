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
    const auto y = DegToRad(yaw);
    const auto p = DegToRad(pitch);
    const auto r = DegToRad(roll);
    
    const auto cy = std::cosf(y);
    const auto sy = std::sinf(y);
    const auto cp = std::cosf(p);
    const auto sp = std::sinf(p);
    const auto cr = std::cosf(r);
    const auto sr = std::sinf(r);
    
    out[0][0] = cy * cr - sy * sp * sr;
    out[0][1] = cy * sr + sy * sp * cr;
    out[0][2] = -sy * cp;
    out[1][0] = -sr * cp;
    out[1][1] = cr * cp;
    out[1][2] = sp;
    out[2][0] = sy * cr + cy * sp * sr;
    out[2][1] = sr * sy - cy * sp * cr;
    out[2][2] = cy * cp;
}

void FromAxisAndAngle(const Vector3d& axis, float angle, Matrix3d& out)
{
    const auto a = DegToRad(angle);
    const auto c = std::cosf(a);
    const auto s = std::sinf(a);

    const Vector3d temp = axis * (1.f - c);

    out[0][0] = temp[0] * axis[0] + c;
    out[0][1] = temp[1] * axis[0] + s * axis[2];
    out[0][2] = temp[2] * axis[0] - s * axis[1];
    out[1][0] = temp[0] * axis[1] - s * axis[2];
    out[1][1] = temp[1] * axis[1] + c;
    out[1][2] = temp[2] * axis[1] + s * axis[0];
    out[2][0] = temp[0] * axis[2] + s * axis[1];
    out[2][1] = temp[1] * axis[2] - s * axis[0];
    out[2][2] = temp[2] * axis[2] + c;
}

void MatrixAdd(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{
    out.Init(lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1], lhs[0][2] + rhs[0][2],
             lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1], lhs[1][2] + rhs[1][2],
             lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1], lhs[2][2] + rhs[2][2]);
}

void MatrixSubtract(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{
    out.Init(lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1], lhs[0][2] - rhs[0][2],
             lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1], lhs[1][2] - rhs[1][2],
             lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1], lhs[2][2] - rhs[2][2]);
}

void MatrixMultiply(const Matrix3d& lhs, const Matrix3d& rhs, Matrix3d& out)
{
    out.Init(lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
             lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
             lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2],
             lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
             lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
             lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2],
             lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],
             lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],
             lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]);
}

void MatrixInverse(const Matrix3d& in, Matrix3d& out)
{

}

void MatrixAdd(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{
    out.Init(lhs[0][0] + rhs[0][0], lhs[0][1] + rhs[0][1], lhs[0][2] + rhs[0][2], lhs[0][3] + rhs[0][3],
             lhs[1][0] + rhs[1][0], lhs[1][1] + rhs[1][1], lhs[1][2] + rhs[1][2], lhs[1][3] + rhs[1][3],
             lhs[2][0] + rhs[2][0], lhs[2][1] + rhs[2][1], lhs[2][2] + rhs[2][2], lhs[2][3] + rhs[2][3],
             lhs[3][0] + rhs[3][0], lhs[3][1] + rhs[3][1], lhs[3][2] + rhs[3][2], lhs[3][3] + rhs[3][3]);
}

void MatrixSubtract(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{
    out.Init(lhs[0][0] - rhs[0][0], lhs[0][1] - rhs[0][1], lhs[0][2] - rhs[0][2], lhs[0][3] - rhs[0][3],
             lhs[1][0] - rhs[1][0], lhs[1][1] - rhs[1][1], lhs[1][2] - rhs[1][2], lhs[1][3] - rhs[1][3],
             lhs[2][0] - rhs[2][0], lhs[2][1] - rhs[2][1], lhs[2][2] - rhs[2][2], lhs[2][3] - rhs[2][3],
             lhs[3][0] - rhs[3][0], lhs[3][1] - rhs[3][1], lhs[3][2] - rhs[3][2], lhs[3][3] - rhs[3][3]);
}

void MatrixMultiply(const Matrix4d& lhs, const Matrix4d& rhs, Matrix4d& out)
{
    out.Init(lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0],
             lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1],
             lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2],
             lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3],
             lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0],
             lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1],
             lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2],
             lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3],
             lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0],
             lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1],
             lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][2] * rhs[3][2],
             lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][2] * rhs[3][3],
             lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0],
             lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1],
             lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][2] * rhs[3][2],
             lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3] + lhs[3][2] * rhs[3][3]);
}

void MatrixInverse(const Matrix4d& in, Matrix4d& out)
{

}

void MatrixBuildAffine(const Vector3d& translation, const Matrix3d& rotation,
                              const Vector3d& scale, Matrix4d& out)
{
    out.X().Init(scale[0] * rotation[0][0], scale[1] *
        rotation[0][1], scale[2] * rotation[0][2], 0.f);
    out.Y().Init(scale[0] * rotation[1][0], scale[1] *
        rotation[1][1], scale[2] * rotation[1][2], 0.f);
    out.Z().Init(scale[0] * rotation[2][0], scale[1] *
        rotation[2][1], scale[2] * rotation[2][2], 0.f);
    out.W().Init(translation, 1.f);
}

void MatrixBuildPerspective(float fov, float aspect_ratio, float near_clip_plane,
                                   float far_clip_plane, Matrix4d& out)
{
    const float tg = std::tanf(fov * .5f);

    assert(tg && aspect_ratio && near_clip_plane != far_clip_plane);

    out[1][1] = 1.f / tg;
    out[0][0] = out[1][1] / aspect_ratio;
    out[2][2] = far_clip_plane / (far_clip_plane - near_clip_plane);
    out[3][2] = near_clip_plane * far_clip_plane / (near_clip_plane - far_clip_plane);
    out[2][3] = 1.f;

    out[0][1] = out[0][2] = out[0][3] = 0.f;
    out[1][0] = out[1][2] = out[1][3] = 0.f;
    out[2][0] = out[2][1] = 0.f;
    out[3][0] = out[3][1] = out[3][3] = 0.f;
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