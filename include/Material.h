#pragma once

#include "Shader.h"
#include "Log.h"
#include <map>
#include <string.h>

namespace Renderer
{
    struct MaterialProperty
    {
        Uniform* uniform;
    };

    struct Material
    {
        const char* name;
        Shader* shader;
     
        std::map<std::string, MaterialProperty> properties;
    };

    // CAUTION: this asumes that shader has it uniforms registered...
    Material buildMaterial(Shader& shader, const char* name);

    template<typename T>
    bool setValue(Material& mat, const char* name, const T& value)
    {
        auto it = mat.properties.find(name);;
        if(it == mat.properties.end())
        {
            char msg[512];
            sprintf(msg, "%s property not found in material: %s...", name, mat.name);
            Log::print({"ERROR:MATERIAL::SET_PROPERTY_VALUE", msg});
            return false;
        }

        MaterialProperty& prop = (*it).second;
        if(strcmp(typeid(value).name(), prop.uniform->type) != 0)
        {
            char msg[512];
            sprintf(
                msg, 
                "Material(%s) %s property's type it's %s received %s", 
                mat.name, 
                name, 
                prop.uniform->type, 
                typeid(value).name()
            );
            Log::print({"ERROR:MATERIAL::SET_PROPERTY_VALUE", msg});
            return false;
        }

        Renderer::setUniform(*mat.shader, *(prop.uniform), &value);  

        return true;
    }

    void use(const Material& mat);
};