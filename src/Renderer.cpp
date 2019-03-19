#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Renderer.h"
#include "Triangle.h"

void Renderer::setScreenDimensions(int w, int h)
{
    Renderer::state.screen.Width  = w;
    Renderer::state.screen.Height = h;
}

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

// TODO: just testing
#include "Transform.h"
static float translation = -3.0;
static float scaleFactor = -3.0;
static float rotation = -6.28319;
void Renderer::renderState(RendererState* rs)
{
    // TODO: just testing
    Transform tr;
    Renderer::translate(tr, translation, translation, 0);
    Renderer::scale(tr, scaleFactor);
    Geometry::Quaternion q = Geometry::quat(0, 0, 1, rotation);
    tr.rotation = q;
    //Renderer::rotate(tr, q);
    translation += 0.05;
    if(translation > 3)
    {
        translation = -3.0;
    }
    scaleFactor += 0.05;
    if(scaleFactor > 3)
    {
        scaleFactor = -3.0;
    }
    rotation += 0.05;
    if(rotation > 6.28319)
    {
        rotation = -6.28319;
    }
    Geometry::Mat4 modelMatrix = Renderer::modelMat(tr);

    glPushMatrix();
    glMultMatrixf(modelMatrix.m);
    // glTranslatef(1.0, 0.0, 0.0);

    renderPoints(rs->points.data(), rs->points.size());
    renderLines(rs->lines.data(), rs->lines.size());
    renderModels(rs->models.data(), rs->models.size());

    glPopMatrix();
}

// TODO: just testing
#include "Shader.h"
#include "Material.h"
#include <chrono>
#include <thread>

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

    glViewport(0, 0, state.screen.Width, state.screen.Height);

    glClearColor(0.20, 0.20, 0.20, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)state.screen.Width/(float)state.screen.Height, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    renderState(&Renderer::state);

    glutSwapBuffers();

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    glutPostRedisplay();
}