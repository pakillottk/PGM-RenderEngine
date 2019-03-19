#include "Transform.h"
#include "Transform.h"

Geometry::Mat4 Renderer::modelMat(const Transform& t)
{
    return Geometry::translation(t.position) * Geometry::rotation(t.rotation.Axis, t.rotation.W) * Geometry::scale(t.scale);
}

Geometry::Vector3D& Renderer::translate(Transform& tr, const Geometry::Vector3D& translation)
{
    tr.position = tr.position + translation;
    return tr.position;
}

Geometry::Vector3D& Renderer::translate(Transform& tr, float x, float y, float z)
{
    tr.position = tr.position + Geometry::vec3(x, y, z);
    return tr.position;
}

Geometry::Quaternion& Renderer::rotate(Transform& tr, Geometry::Quaternion& q)
{
    tr.rotation = q * tr.rotation;
    return tr.rotation;
}

Geometry::Quaternion& Renderer::rotate(Transform& tr, const Geometry::Vector3D& axis, float angle)
{
    // TODO: quat multiplication
    return tr.rotation;
}

Geometry::Quaternion& Renderer::rotate(Transform& tr, float x, float y, float z, float angle)
{
    // TODO: quat multiplication
    return tr.rotation;    
}

Geometry::Vector3D& Renderer::scale(Transform& tr, const Geometry::Vector3D& scale)
{
    tr.scale = tr.scale * scale;
    return tr.scale;
}

Geometry::Vector3D& Renderer::scale(Transform& tr, float x, float y, float z)
{
    tr.scale = tr.scale * Geometry::vec3(x, y, z);
    return tr.scale;
}

Geometry::Vector3D& Renderer::scale(Transform& tr, float scale)
{
    tr.scale = tr.scale * scale;
    return tr.scale;
}