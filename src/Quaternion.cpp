#include "Quaternion.h"
#include "Mat4.h"
#include "LoopTemplates.h"
#include <cmath>

Geometry::Quaternion Geometry::quat(float x, float y, float z, float angle)
{
    Quaternion q;
    q.Axis = vec3(x, y, z);
    q.W = angle;

    return q;
}    

Geometry::Quaternion Geometry::quat(const Vector3D& axis, float angle)
{
    Quaternion q;
    q.Axis = axis;
    q.W = angle;

    return q;
}

Geometry::Quaternion Geometry::conjugate(const Quaternion& q)
{
    Quaternion conj(q);
    conj.Axis = conj.Axis * -1;
    return conj; 
}

float Geometry::squaredNorm(const Quaternion& q)
{
    return Geometry::length(q.Axis) + q.W * q.W;
}

float Geometry::norm(const Quaternion& q)
{
    return sqrt(squaredNorm(q));
}

Geometry::Quaternion& Geometry::normalize(Quaternion& q)
{
    short i = 0;
    float norm = Geometry::norm(q);
    LOOP3(q.data[i++] /= norm;)

    return q;
}