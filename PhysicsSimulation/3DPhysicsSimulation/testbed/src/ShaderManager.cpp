#include "ShaderManager.hpp"

ShaderManager::ShaderManager(DynamicAllocator& allocator) 
    : Manager(), 
      _allocator(allocator)
{

}

ShaderManager::~ShaderManager()
{

    
}

void ShaderManager::registerShaderProgram(const char* shaderName)
{
    _logger.logf(LogLevel::DEBUG, "Registering shader program: %s", shaderName);
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

    _logger.logf(LogLevel::DEBUG, "Shaderprogram registered: %s", shaderName);
}

void ShaderManager::registerShaderProgram(const char* shaderName, const char* vertexName, const char* fragmentName)
{
    _logger.logf(LogLevel::DEBUG, "Registering shader program: %s", shaderName);
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

    _logger.logf(LogLevel::DEBUG, "Shaderprogram registered: %s", shaderName);
}

void ShaderManager::renameShaderProgram(const char* oldName, const char* newName)
{
    _logger.logf(LogLevel::DEBUG, "Renaming shader: %s", oldName);
    
    auto it = shaderPrograms.find(oldName);
    if (it == shaderPrograms.end()) {
        _logger.logf(LogLevel::ERROR, "shader not found: %s", oldName);
        return;
    }
    it = shaderPrograms.find(newName);
    if (it != shaderPrograms.end()) {
        _logger.logf(LogLevel::ERROR, "shader name %s already has a shaderprogram!", newName);
        return;
    }




    shaderPrograms[newName] = shaderPrograms[oldName];
    shaderPrograms.erase(oldName);
    _logger.logf(LogLevel::DEBUG, "Shaderprogram %s renamed to", oldName, newName);
}

void ShaderManager::resigterShader(const std::string& shaderName, Shader* shader)
{
    _logger.logf(LogLevel::DEBUG, "Registering Shader Object: %s", shaderName);
    auto it = shaderMap.find(shaderName);
    if (it == shaderMap.end()) {
        shaderMap[shaderName] = shader;
        _logger.logf(LogLevel::DEBUG, "Shader Object Registered: %s", shaderName);
    }

    _logger.logf(LogLevel::ERROR, "Shader Object %s is already registered!", shaderName);
}

void ShaderManager::registerShader(const std::string& shaderName, std::vector<uint*> shaderPrograms)
{
    _logger.logf(LogLevel::DEBUG, "Registering Shader Object %s", shaderName);
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end()) {
        _logger.logf(LogLevel::ERROR, "Shader Object %s is already registered!", shaderName);
        return;
    }

    _logger.logf(LogLevel::DEBUG, "Creating shader %s", shaderName);
    // Create shader using the dynamic allocator
    Shader* shader = static_cast<Shader*>(_allocator.allocate(sizeof(Shader)));
    shader->shaderPrograms = shaderPrograms;

    shaderMap[shaderName] = shader;
    _logger.logf(LogLevel::DEBUG, "Shader Object Created and Registered: %s", shaderName);
}


void ShaderManager::registerShader(const std::string& shaderName, std::vector<std::string> shaderProgramNames)
{
    _logger.logf(LogLevel::DEBUG, "Registering Shader Object %s", shaderName);
    auto it = shaderMap.find(shaderName);
    if (it != shaderMap.end()) {
        _logger.logf(LogLevel::ERROR, "Shader Object %s is already registered!", shaderName);
        return;
    }

    std::string listedNames;
    for (std::string& s : shaderProgramNames ) listedNames += (s + ' ');

    _logger.logf(LogLevel::DEBUG, "Creating shader %s from listed shaderPrograms: ", shaderName);
    _logger.logf(LogLevel::DEBUG, "\t %s", listedNames);
    std::vector <uint*> shaderProgramList;

    for (std::string s : shaderProgramNames) {
        shaderProgramList.push_back(shaderPrograms[s]);
    }
    // Allocate memory and construct the Shader 
    void* shaderMemory = _allocator.allocate(sizeof(Shader));
    Shader* shader = new (shaderMemory) Shader(std::move(shaderProgramList)); 


    shaderMap[shaderName] = shader;    
    _logger.logf(LogLevel::DEBUG, "Shader Object Created and Registered: %s", shaderName);
}
