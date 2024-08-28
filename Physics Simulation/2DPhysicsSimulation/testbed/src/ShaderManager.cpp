#include "ShaderManager.hpp"

ShaderManager::ShaderManager()
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

    shaderPrograms[shaderName] = shaderProgram;

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

    shaderPrograms[shaderName] = shaderProgram;

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