#include "Vector3D.h"
#include <cmath>

Geometry::Vector3D Geometry::vec3(float x, float y, float z)
{
    Vector3D v;
    v.X = x; v.Y = y; v.Z = z;

    return v;
}

float Geometry::lengthSquared(const Vector3D& v)
{
    float l = 0;
    short i = 0;
    LOOP3(l += v.data[i] * v.data[i]; i++;)

    return l;
}

float Geometry::length(const Vector3D& v)
{
    return sqrt(lengthSquared(v));
}

Geometry::Vector3D& Geometry::normalize(Vector3D& v)
{
    float l = length(v);
    short i = 0;
    LOOP3(v.data[i] /= l; i++;)

    return v;
}

float Geometry::dot(const Vector3D& v1, const Vector3D& v2)
{
    float dot = 0;

    short i = 0;
    LOOP3(dot += v1.data[i] * v2.data[i]; i++;)

    return dot;
}

Geometry::Vector3D Geometry::cross(const Vector3D& v1, const Vector3D& v2)
{
    Vector3D cross;
    cross.data[0] = v1.data[1] * v2.data[2] - v1.data[2] * v2.data[1]; 
    cross.data[1] = v1.data[0] * v2.data[2] - v1.data[2] * v2.data[0]; 
    cross.data[2] = v1.data[0] * v2.data[1] - v1.data[1] * v2.data[0]; 

    return cross;
}