#include "Mat4.h"
#include <cmath>

Geometry::Mat4 Geometry::Mat4::operator*(const Mat4& mat)
{
    Mat4 mult;
    memset(mult.m, 0, sizeof(float) * 16);

    for(short i = 0; i < 4; i++)
    {
        for(short j = 0; j < 4; j++)
        {
            for(short k = 0; k < 4; ++k)
            {
                mult.mm[i][j] += mm[i][k] * mat.mm[k][j];
            }
        }
    }

    return mult;
}

Geometry::Vector3D Geometry::Mat4::operator*(const Vector3D& v)
{
    float v4[] = { v.X, v.Y, v.Z, 1.0 };
    float mult[] = { 0.0, 0.0, 0.0, 0.0};
    for(short i = 0; i < 4; i++)
    {
        for(short j = 0; j < 4; j++)
        {
            mult[i] += mm[i][j] * v4[j];
        }
    }

    return vec3(mult[0], mult[1], mult[2]);
}

Geometry::Mat4 Geometry::mat4()
{
    Mat4 m;
    return identity(m);
}

Geometry::Mat4& Geometry::identity(Mat4& m)
{
    memset(m.m, 0, sizeof(float) * 16);
    m.m00 = 1;
    m.m11 = 1;
    m.m22 = 1;
    m.m33 = 1;

    return m;
}

Geometry::Mat4 Geometry::translation(const Vector3D& t)
{
    return translation(t.X, t.Y, t.Z);
}

Geometry::Mat4 Geometry::translation(float x, float y, float z)
{
    Mat4 mat = mat4();
    mat.m03 = x;
    mat.m13 = y;
    mat.m23 = z;

    return mat;
}

Geometry::Mat4 Geometry::scale(const Vector3D& s)
{
    return scale(s.X, s.Y, s.Z);
}

Geometry::Mat4 Geometry::scale(float x, float y, float z)
{
    Mat4 mat = mat4();
    mat.m00 = x;
    mat.m11 = y;
    mat.m22 = z;

    return mat;
}

Geometry::Mat4 Geometry::scale(float s)
{
    Mat4 mat = mat4();
    mat.m00 = s;
    mat.m11 = s;
    mat.m22 = s;

    return mat;
}

Geometry::Mat4 Geometry::rotation(const Quaternion& q)
{
    Mat4 mat = mat4();

    mat.m00 = 1 - 2 * q.Y * q.Y - 2 *q.Z * q.Z;
    mat.m01 = 2 * q.X * q.Y - 2 * q.Z * q.W;
    mat.m02 = 2 * q.X * q.Z + 2 * q.Y * q.W;

    mat.m10 = 2 * q.X * q.Y + 2 *q.Z * q.W;
    mat.m11 = 1 - 2 * q.X * q.X - 2 * q.Z * q.Z;
    mat.m12 = 2 * q.Y * q.Z - 2 * q.X * q.W;

    mat.m20 = 2 * q.X * q.Z - 2 * q.Y * q.W;
    mat.m21 = 2 * q.Y * q.Z + 2 * q.X * q.W;
    mat.m22 = 1 - 2 * q.X * q.X - 2 * q.Y * q.Y;

    return mat;  
}

Geometry::Mat4 Geometry::rotation(const Vector3D& axis, float angle)
{
    return Geometry::rotation(axis.X, axis.Y, axis.Z, angle);
}

Geometry::Mat4 Geometry::rotation(float x, float y, float z, float angle)
{
    Mat4 mat = mat4();

    float angCos = cos(angle);
    float angSin = sin(angle);
    float oneMinusCos = 1 - angCos;

    mat.m00 = angCos + (x * x * oneMinusCos);
    mat.m01 =  (x * y * oneMinusCos) - (x * angSin);
    mat.m03 =  (x * z * oneMinusCos) + (y * angSin);

    mat.m10 = (y * x * oneMinusCos) + (z * angSin);
    mat.m11 =  angCos + (y*y*oneMinusCos);
    mat.m13 =  (y * z * oneMinusCos) - (x * angSin);

    mat.m20 = (z * x * oneMinusCos) - (y * angSin);
    mat.m21 =  (z * y * oneMinusCos) + (x*angSin);
    mat.m23 =  angCos + (z * z * oneMinusCos);

    return mat;
}