#pragma once

#include <vector>
#include "Material.h"
// #include "Entity.h"
#include "Point3D.h"
#include "Line.h"
#include "Model.h"

namespace Renderer
{
    struct RenderBuffer
    {
        Material material;
        // TODO: entities to render with this material
    };

    union Screen
    {
        unsigned dimensions[2];
        struct
        {
            int Width;
            int Height;
        };

        Screen()
        {
            dimensions[0] = dimensions[1] = 0;
        }
    };

    struct RendererState
    {
        Screen screen;

        std::vector<Geometry::Point3D> points;
        std::vector<Geometry::Line> lines;
        std::vector<Renderer::Model> models;
    
        // TODO: use buffers
    };

    typedef void (state_mutation_cb)(RendererState*); 

    namespace
    {
        static RendererState state;
    }

    void setScreenDimensions(int w, int h);

    void mutateState(state_mutation_cb cb);

    void renderModels(Model* models, unsigned mcount);
    void renderLines(Geometry::Line* lines, unsigned lcount);
    void renderPoints(Geometry::Point3D* points, unsigned pcount);
    
    void renderState(RendererState* rs);
    void render();
};