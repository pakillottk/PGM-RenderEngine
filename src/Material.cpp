#include "Material.h"
#include "Log.h"

Renderer::Material Renderer::buildMaterial(Renderer::Shader& shader, const char* name)
{
    Material mat;
    mat.name = name;
    mat.shader = & shader;

    // bind the uniforms to material properties
    auto it = shader.uniforms.begin();
    while(it != shader.uniforms.end())
    {
        Renderer::Uniform& uniform = (*it).second;

        MaterialProperty prop;
        prop.uniform = &uniform;
        mat.properties.insert( std::pair<std::string, MaterialProperty>((*it).first, prop) );

        it++;
    }

    return mat;
}

void Renderer::use(const Renderer::Material& mat)
{
     // bind the shader
    use(*mat.shader);
}