#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Renderer.h"
#include "Triangle.h"

void Renderer::mutateState(state_mutation_cb cb)
{
    cb(&Renderer::state);
}

void Renderer::renderModels(Renderer::Model* models, unsigned mcount)
{
    glColor3f(1.0, 1.0, 0.0);

    // TODO: this is horrible... (vao would solve it)
    
    for(unsigned i = 0; i < mcount; i++)
    {
        const Model& m = models[i];
        glBegin(GL_TRIANGLES);
        for(unsigned t = 0; t < m.triangles.size(); t++)
        {
            const Geometry::Triangle& tri = m.triangles[t];
            for(short v = 0; v < 3; v++)
            {
                glVertex3fv(m.vertices[tri.data[v]].data);
            }
        }
        glEnd();
    }   
}

void Renderer::renderLines(Geometry::Line* lines, unsigned lcount)
{
    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_LINES);
    for(unsigned i = 0; i < lcount; i++)
    {
        glVertex3fv(lines[i].data);    
    }
    glEnd();
}

void Renderer::renderPoints(Geometry::Point3D* points, unsigned pcount)
{
    //TODO: vao
    glColor3f(1.0, 0.0, 0.0);

    glPointSize(5.0);
    glBegin(GL_POINTS);
    for(unsigned i = 0; i < pcount; i++)
    {
        glVertex3fv(points[i].data);    
    }
    glEnd();
}

void Renderer::renderState(RendererState* rs)
{
    renderPoints(rs->points.data(), rs->points.size());
    renderLines(rs->lines.data(), rs->lines.size());
    renderModels(rs->models.data(), rs->models.size());
}

// TODO: just testing
#include "Shader.h"
#include "Material.h"

void Renderer::render()
{
    // TODO: just testing
    Shader s = buildShader("shaders/points/points.vert", "shaders/points/points.frag");
    Material mat = buildMaterial(s, "test-mat");
    setValue<float>(mat, "uniform1", 1.0);
    setValue<int>(mat, "uniform2", 1);
    use(mat);
    glUseProgram(0);
    // ===========================

    glClearColor(0.20, 0.20, 0.20, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 2, 1, 10);;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    renderState(&Renderer::state);

    glutSwapBuffers();
}