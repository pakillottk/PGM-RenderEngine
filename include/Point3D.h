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

        Point3D& operator+(const Point3D& p)
        {
            unsigned i = 0;
            LOOP3(data[i] += p.data[i]; i++;)
            return *this;
        }

        Point3D& operator*(const Point3D& p)
        {
            unsigned i = 0;
            LOOP3(data[i] *= p.data[i]; i++;)
            return *this;
        }

        Point3D& operator*(float v)
        {
            unsigned i = 0;
            LOOP3(data[i] *= v; i++;)
            return *this;
        }
    };    

    // TODO: builders and methods
};