#pragma once

#include <string.h>
#include "Point3D.h"

namespace Geometry
{
    union Line
    {
        float data[6];
        Point3D points[2];
        struct
        {
            Point3D p1;
            Point3D p2;
        };
    };

    // TODO: builders and methods
}; // Geometry

