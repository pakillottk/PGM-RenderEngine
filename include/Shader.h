#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <stdio.h>
#include <stdlib.h>
#include <map>

namespace Renderer
{
    struct Uniform
    {
        const char* name;
        const char* type;
        unsigned location;

        Uniform(){}
        Uniform(const Uniform& other)
        {
            name = other.name;
            type = other.type;
            location = other.location;
        }
    };

    struct Shader
    {
        unsigned id;
        std::map<std::string, Uniform> uniforms;
    };
    
    Shader buildShader(const char* vertexFile, const char* fragmentFile);
    void use(const Shader& shader);
    bool registerUniforms(Shader& shader);
    bool registerUniform(Shader& shader, const char* name, const char* type);
    bool setUniform(const Shader& shader, const Uniform& uniform, const void* value);
    bool setUniform(const Shader& shader, const char* uniform, const void* value);
};