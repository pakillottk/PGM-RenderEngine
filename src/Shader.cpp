#include "Shader.h"
#include "IO.h"
#include "Log.h"

#include <string.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

int createAndCompileShader(const char* code, GLenum type)
{
    int id = glCreateShader(type);
    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);
    // print compile errors if any
    int success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(id, 512, NULL, infoLog);

        Log::print({"ERROR::SHADER::COMPILATION_FAILED",  infoLog});
    
        return -1;
    };

    return id;
}

Renderer::Shader Renderer::buildShader(const char* vertexFile, const char* fragmentFile)
{
    Shader s;

    const char* vertexCode = IO::readTextFile(vertexFile);
    const char* fragmentCode = IO::readTextFile(fragmentFile);

    int vertex = createAndCompileShader(vertexCode, GL_VERTEX_SHADER);
    int fragment = createAndCompileShader(fragmentCode, GL_FRAGMENT_SHADER);

    if(vertex < 0 || fragment < 0)
    {
        // something failed...
        return s;
    }

    // create and link
    s.id = glCreateProgram();
    glAttachShader(s.id, vertex);
    glAttachShader(s.id, fragment);
    glLinkProgram(s.id);
    // print linking errors if any
    int success = 0;
    glGetProgramiv(s.id, GL_LINK_STATUS, &success);
    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(s.id, 512, NULL, infoLog);
        Log::print({"ERROR::SHADER::LINKING_FAILED",  infoLog});

        s.id = -1;
        return s;
    }

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if(!registerUniforms(s))
    {
        Log::print({"ERROR::SHADER::REGISTER_UNIFORMS",  "couldn't register all the uniforms..."});
        glDeleteProgram(s.id);
        s.id = -1;
    }

    return s;
}

void Renderer::use(const Renderer::Shader& shader)
{
    glUseProgram(shader.id);
}

const char* getNativeType(GLenum glType)
{
    switch (glType)
    {
        case GL_FLOAT:
            return typeid(float).name();
        case GL_INT:
            return typeid(int).name();
        case GL_BOOL:
            return typeid(bool).name();
        
        // TODO: all types

        default:
            return NULL;
    }
}

bool Renderer::registerUniforms(Renderer::Shader& shader)
{
    int nUniforms = 0;
    glGetProgramiv(shader.id, GL_ACTIVE_UNIFORMS, &nUniforms);

    for(int i = 0; i < nUniforms; i++)
    {
        char name[512];
        int nlength = 0;
        GLenum type = 0;
        int size = 0;
        glGetActiveUniform(shader.id, i, 512, &nlength, &size, &type, name);

        if(!registerUniform(shader, name, getNativeType(type)))
        {
            return false;
        }
    }

    return shader.uniforms.size() == nUniforms;
}

bool Renderer::registerUniform(Renderer::Shader& shader, const char* name, const char* type)
{
    Uniform u;
    u.name = name;
    u.type = type;
    int location = glGetUniformLocation(shader.id, name);
    
    if(location < 0)
    {
        char msg[512];
        sprintf(msg, "%s is not a valid uniform...", name);
        Log::print({"ERROR:SHADER::REGISTER_UNIFORM", msg});
        return false;
    }

    u.location = location;
    shader.uniforms.insert( std::pair<std::string, Uniform>(std::string(name), u) );
    return true;
}

 bool Renderer::setUniform(const Renderer::Shader& shader, const Renderer::Uniform& uniform, const void* value)
 {
    if(strcmp(uniform.type, typeid(int).name()) == 0)
    {
        int* v = (int*)value;
        glUniform1i(uniform.location, *v); 
    }
    else if(strcmp(uniform.type, typeid(float).name()))
    {
        float* v = (float*)value;
        glUniform1f(uniform.location, *v); 
    }
    else if(strcmp(uniform.type, typeid(bool).name()))
    {
        bool* v = (bool*)value;
        glUniform1i(uniform.location, (int)*v);
    }
    else
    {
        char msg[512];
        sprintf(msg, "%s is not a valid type...", uniform.type);
        Log::print({"ERROR:SHADER::SET_UNIFORM", msg});
        return false;
    }

    return true;
 }

bool Renderer::setUniform(const Renderer::Shader& shader, const char* name, const void* value)
{
    auto it = shader.uniforms.find(name);
    if(it == shader.uniforms.end())
    {
        char msg[512];
        sprintf(msg, "%s not registered in this shader...", name);
        Log::print({"ERROR:SHADER::SET_UNIFORM", msg});
        return false;
    }

    const Uniform& uniform = (*it).second;    
    return setUniform(shader, uniform, value);
}