#pragma once

#include "LoopTemplates.h"
#include <string.h>

namespace Geometry
{
    union Point3D
    {
        float data[3];
        struct
        {
            float X;
            float Y;
            float Z;
        };
    };    

    // TODO: builders and methods
};