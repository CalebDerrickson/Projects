// Managing class to handle working with shaders


#pragma once
#include "ShaderActions.hpp"
#include "Shader.hpp"
#include "utils.hpp"
#include <unordered_map>
#include <vector>
#define SHADER_PATH "../testbed/assets/shaders/"

class ShaderManager{
public:
    ShaderManager();
    ~ShaderManager();

    void registerShaderProgram(const char* shaderName);
    void registerShaderProgram(const char* shaderName, const char* vertexName, const char* fragmentName);
    void renameShaderProgram(const char* oldName, const char* newName);

    // Shader Program map
    std::unordered_map<const char*, uint> shaderPrograms;

    // Shader Map
    // std::vector<Shader*> 
};