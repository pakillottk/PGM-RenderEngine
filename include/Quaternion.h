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

        Quaternion()
        {
            memset(data, 0, sizeof(float)*4);
            data[0] = 1;
        }

        Quaternion(const Quaternion& q)
        {
            memcpy(data, q.data, sizeof(Quaternion));
        }

        Quaternion& operator=(const Quaternion& q)
        {
            memcpy(data, q.data, sizeof(Quaternion));
            return *this;
        }

        Quaternion operator*(const Quaternion& q)
        {
            Quaternion res;
            res.W = q.W * W - q.X * X - q.Y * Y - q.Z * Z;
            res.X = q.W * X + q.X * W - q.Y * Z + q.Z * Y;
            res.Y = q.W * Y + q.X * Z + q.Y * W - q.Z * X;
            res.Z = q.W * Z - q.X * Y + q.Y * X + q.Z * W;

            return res;  
        }
    };

    Quaternion quat(float x = 1, float y = 0, float z = 0, float angle = 0);    
    Quaternion quat(const Vector3D& axis, float angle);
    Quaternion conjugate(const Quaternion& q);
    float squaredNorm(const Quaternion& q);
    float norm(const Quaternion& q);
    Quaternion& normalize(Quaternion& q);
};