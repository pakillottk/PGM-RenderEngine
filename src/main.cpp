#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include "Renderer.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    // init GLUT and create window
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(800, 600);
    
    glutCreateWindow("OpenGL - DOD");

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error %s\n", glewGetErrorString(err));
        exit(1);
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    if (GLEW_ARB_vertex_program)
        fprintf(stdout, "Status: ARB vertex programs available.\n");

    if (glewGetExtension("GL_ARB_fragment_program"))
        fprintf(stdout, "Status: ARB fragment programs available.\n");
    if (glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite"))
        fprintf(stdout, "Status: ARB point sprites available.\n");

	// register callbacks
    glutDisplayFunc(Renderer::render);
    glutReshapeFunc([](int w, int h)
    {
        Renderer::setScreenDimensions(w, h);
    });

    // TODO: this is just for debugging
    Renderer::mutateState([](Renderer::RendererState* state)
    {
        for(int i = 0; i < 100; i++)
        {
            Geometry::Point3D p;
            p.X = i; p.Y = 0; p.Z = 0;
            state->points.push_back(p);

            Geometry::Line l;
            l.p1.X = i*10; l.p1.Y = i * 10; l.p1.Z = 0;
            l.p2.X = i*20; l.p2.Y = i * 20; l.p2.Z = 0;
            state->lines.push_back(l);
        }

        Renderer::Model model;
        Geometry::Triangle tri;
        tri.a = 0; tri.b = 1; tri.c = 2;
        Geometry::Point3D p1, p2, p3;
        p1.X = -3; p1.Y = -1; p1.Z = 0;
        p2.X =  3; p2.Y = -1; p2.Z = 0;
        p3.X =  0; p3.Y =  1; p3.Z = 0;

        model.vertices.push_back(p1);
        model.vertices.push_back(p2);
        model.vertices.push_back(p3);
        model.triangles.push_back(tri);

        state->models.push_back(model);
    });
	// enter GLUT event processing cycle
    glutMainLoop();

    return 0;
}