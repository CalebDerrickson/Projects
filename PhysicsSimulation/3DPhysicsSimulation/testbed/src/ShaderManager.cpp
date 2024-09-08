#include "ShaderManager.hpp"

ShaderManager::ShaderManager(DynamicAllocator& allocator) 
    : _allocator(allocator)
{

}

ShaderManager::~ShaderManager()
{

    
}

void ShaderManager::registerShaderProgram(const char* shaderName)
{
    std::string shader_path(SHADER_PATH);
    std::string FileName(shaderName);

    // vertexShader
    uint vertexShader = shader::compileShader(shader_path + "vertex_" + FileName + ".glsl", GL_VERTEX_SHADER);

    // fragmentShader
    uint fragmentShader = shader::compileShader(shader_path + "fragment_" + FileName + ".glsl", GL_FRAGMENT_SHADER);
    
    // Creating shader programs for linking
    uint shaderProgram = glCreateProgram();
    shader::linkShaderProgram(shaderProgram, vertexShader, fragmentShader);

    uint* allocatedMemory = static_cast<uint*>(_allocator.allocate(sizeof(uint)));
    *allocatedMemory = shaderProgram;

    shaderPrograms[shaderName] = allocatedMemory;

    std::cout<<"Shader Registered: "<<shaderName<<std::endl;
}

void ShaderManager::registerShaderProgram(const char* shaderName, const char* vertexName, const char* fragmentName)
{
    std::string resource_path(SHADER_PATH);
    std::string vertexFileName(vertexName);
    std::string fragmentFileName(fragmentName);

    // vertexShader
    uint vertexShader = shader::compileShader(resource_path + "vertex_" + vertexFileName + ".glsl", GL_VERTEX_SHADER);

    // fragmentShader
    uint fragmentShader = shader::compileShader(resource_path + "fragment_" + fragmentFileName + ".glsl", GL_FRAGMENT_SHADER);
    
    // Creating shader programs for linking
    uint shaderProgram = glCreateProgram();
    shader::linkShaderProgram(shaderProgram, vertexShader, fragmentShader);
    
    uint* allocatedMemory = static_cast<uint*>(_allocator.allocate(sizeof(uint)));
    *allocatedMemory = shaderProgram;

    shaderPrograms[shaderName] = allocatedMemory;

    std::cout<<"Shader Registered: "<<shaderName<<std::endl;

}

void ShaderManager::renameShaderProgram(const char* oldName, const char* newName)
{
    if (shaderPrograms.find(oldName) == shaderPrograms.end() ||
        shaderPrograms.find(newName) != shaderPrograms.end()) {
        return;
    }

    shaderPrograms[newName] = shaderPrograms[oldName];
    shaderPrograms.erase(oldName);
    std::cout<<"Shader "<<oldName<<" renamed to "<<newName<<std::endl; 
}

void ShaderManager::resigterShader(const std::string& shaderName, Shader* shader)
{
    auto it = shaderMap.find(shaderName);
    if (it == shaderMap.end()) {
        shaderMap[shaderName] = shader;
    }

}

void ShaderManager::registerShader(const std::string& shaderName, std::vector<uint*> shaderPrograms)
{
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end()) return;

    // Create shader using the dynamic allocator
    Shader* shader = static_cast<Shader*>(_allocator.allocate(sizeof(Shader)));
    shader->shaderPrograms = shaderPrograms;

    shaderMap[shaderName] = shader;
}


void ShaderManager::registerShader(const std::string& shaderName, std::vector<std::string> shaderProgramNames)
{
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end()) return;

    std::vector <uint*> shaderProgramList;

    for (std::string s : shaderProgramNames) {
        shaderProgramList.push_back(shaderPrograms[s]);
    }
    // Allocate memory and construct the Shader 
    void* shaderMemory = _allocator.allocate(sizeof(Shader));
    Shader* shader = new (shaderMemory) Shader(std::move(shaderProgramList)); 


    shaderMap[shaderName] = shader;    
}
