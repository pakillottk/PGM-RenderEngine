#include "Quaternion.h"
#include "Mat4.h"

Geometry::Quaternion Geometry::quat(float x, float y, float z, float angle)
{
    Quaternion q;
    q.Axis = vec3(x, y, z);
    q.W = angle;

    return q;
}    

Geometry::Quaternion Geometry::quat(const Vector3D axis, float angle)
{
    Quaternion q;
    q.Axis = axis;
    q.W = angle;

    return q;
}

Geometry::Mat4 Geometry::quatMatrix(const Quaternion& q)
{
    return rotation(q);
}