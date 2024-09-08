// Managing class to handle working with shaders


#pragma once
#include <unordered_map>
#include <vector>

#include "ShaderActions.hpp"
#include "Shader.hpp"
#include "utils.hpp"
#include "memory/DynamicAllocator.hpp"

#define SHADER_PATH "../testbed/assets/shaders/"

class ShaderManager{
public:
    ShaderManager(DynamicAllocator& allocator);
    ~ShaderManager();

    void registerShaderProgram(const char* shaderName);
    void registerShaderProgram(const char* shaderName, const char* vertexName, const char* fragmentName);
    void renameShaderProgram(const char* oldName, const char* newName);

    void resigterShader(const std::string& shaderName, Shader* shader);

    // creates a shader from shaderPrograms and sets it in shaderMap
    void registerShader(const std::string& shaderName, std::vector<uint*>);

    //  creates a shader from shaderProgram names and sets in shaderMap
    void registerShader(const std::string& shaderName, std::vector<std::string> shaderProgramNames);

    // Shader Program map
    std::unordered_map<std::string, uint*> shaderPrograms;
    
    // Shader Map
    std::unordered_map<std::string, Shader*> shaderMap;

private:
    DynamicAllocator& _allocator;
};