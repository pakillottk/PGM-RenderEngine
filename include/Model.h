#pragma once

#include <vector>
#include "Point3D.h"
#include "Triangle.h"

namespace Renderer
{
    struct Model
    {
        std::vector<Geometry::Point3D>  vertices;
        std::vector<Geometry::Triangle> triangles;
    };  

    // TODO: builders and methods
};
