#pragma once

#include <vector>
#include "Material.h"
#include "Entity.h"
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

    struct RendererState
    {
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

    void mutateState(state_mutation_cb cb);

    void renderModels(Model* models, unsigned mcount);
    void renderLines(Geometry::Line* lines, unsigned lcount);
    void renderPoints(Geometry::Point3D* points, unsigned pcount);
    
    void renderState(RendererState* rs);
    void render();
};