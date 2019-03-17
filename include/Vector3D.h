#pragma once
#include "Point3D.h"

namespace Geometry
{
    typedef Point3D Vector3D;

    Vector3D vec3(float x = 0, float y = 0, float z = 0);
    float lengthSquared(const Vector3D& v);
    float length(const Vector3D& v);
    Vector3D& normalize(Vector3D& v);
    float dot(const Vector3D& v1, const Vector3D& v2);
    Vector3D cross(const Vector3D& v1, const Vector3D& v2);
};