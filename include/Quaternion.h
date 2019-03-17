#pragma once

#include "Vector3D.h"

namespace Geometry
{
    union Mat4;

    union Quaternion
    {
        float data[4];
        Vector3D Axis;
        struct
        {
            float X;
            float Y;
            float Z;
            float W;
        };
    };

    Quaternion quat(float x = 1, float y = 0, float z = 0, float angle = 0);    
    Quaternion quat(const Vector3D axis, float angle);
    Mat4 quatMatrix(const Quaternion& q);
};