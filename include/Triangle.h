#pragma once

namespace Geometry
{
    union Triangle
    {
        unsigned data[3];
        struct
        {
            unsigned a;
            unsigned b;
            unsigned c;
        };        
    };
};