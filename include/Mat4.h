#pragma once

#include "Vector3D.h"
#include "Quaternion.h"

namespace Geometry
{
    union Mat4
    {
        float m[16];
        float mm[4][4];

        struct
        {
            float m0[4];
            float m1[4];
            float m2[4];
            float m3[4];
        };

        struct
        {
            float m00;
            float m10;
            float m20;
            float m30;

            float m01;
            float m11;
            float m21;
            float m31;

            float m02;
            float m12;
            float m22;
            float m32;

            float m03;
            float m13;
            float m23;
            float m33;
        };

        Mat4 operator*(const Mat4& m);
        Vector3D operator*(const Vector3D& v);
    };

    Mat4 mat4();
    Mat4& identity(Mat4& m);
    Mat4 translation(const Vector3D& t);
    Mat4 translation(float x, float y, float z);
    Mat4 scale(const Vector3D& s);
    Mat4 scale(float x, float y, float z);
    Mat4 scale(float s);
    Mat4 rotation(const Quaternion& q);
    Mat4 rotation(const Vector3D& axis, float angle);
    Mat4 rotation(float x, float y, float z, float angle);
};