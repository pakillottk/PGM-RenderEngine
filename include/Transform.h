#pragma once

#include "Vector3D.h"
#include "Quaternion.h"
#include "Mat4.h"

namespace Renderer
{
    struct Transform
    {
        Geometry::Vector3D position;
        Geometry::Quaternion rotation;
        Geometry::Vector3D scale;

        Transform()
        {
            position = Geometry::vec3();
            rotation = Geometry::quat(1, 0, 0, 0);
            scale    = Geometry::vec3(1.0, 1.0, 1.0);
        }
    };

    Geometry::Vector3D& translate(Transform& tr, const Geometry::Vector3D& translation);
    Geometry::Vector3D& translate(Transform& tr, float x, float y, float z);
    
    Geometry::Quaternion& rotate(Transform& tr, const Geometry::Quaternion& q);
    Geometry::Quaternion& rotate(Transform& tr, const Geometry::Vector3D& axis, float angle);
    Geometry::Quaternion& rotate(Transform& tr, float x, float y, float z, float angle);

    Geometry::Vector3D& scale(Transform& tr, const Geometry::Vector3D& scale);
    Geometry::Vector3D& scale(Transform& tr, float x, float y, float z);
    Geometry::Vector3D& scale(Transform& tr, float scale);

    Geometry::Mat4 modelMat(const Transform& t);
};