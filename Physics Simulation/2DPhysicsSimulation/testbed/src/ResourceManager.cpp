#include "ResourceManager.hpp"
#include "ShaderActions.hpp"

// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************


// *******************************
//    CLASS METHOD DEFINITIONS
// *******************************

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::init()
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
}

void ResourceManager::registerShaderProgram(const char* shaderName)
{
    std::string resource_path(RESOURCE_PATH);
    std::string FileName(shaderName);

    // vertexShader
    unsigned int vertexShader = shader::compileShader(resource_path + "vertex_" + FileName + ".glsl", GL_VERTEX_SHADER);

    // fragmentShader
    unsigned int fragmentShader = shader::compileShader(resource_path + "fragment_" + FileName + ".glsl", GL_FRAGMENT_SHADER);
    
    // Creating shader programs for linking
    unsigned int shaderProgram = glCreateProgram();
    shader::linkShaderProgram(shaderProgram, vertexShader, fragmentShader);

    shaderPrograms[shaderName] = shaderProgram;

    std::cout<<"Shader Registered: "<<shaderName<<std::endl;
}

void ResourceManager::registerShaderProgram(const char* shaderName, const char* vertexName, const char* fragmentName)
{
    std::string resource_path(RESOURCE_PATH);
    std::string vertexFileName(vertexName);
    std::string fragmentFileName(fragmentName);

    // vertexShader
    unsigned int vertexShader = shader::compileShader(resource_path + "vertex_" + vertexFileName + ".glsl", GL_VERTEX_SHADER);

    // fragmentShader
    unsigned int fragmentShader = shader::compileShader(resource_path + "fragment_" + fragmentFileName + ".glsl", GL_FRAGMENT_SHADER);
    
    // Creating shader programs for linking
    unsigned int shaderProgram = glCreateProgram();
    shader::linkShaderProgram(shaderProgram, vertexShader, fragmentShader);

    shaderPrograms[shaderName] = shaderProgram;

    std::cout<<"Shader Registered: "<<shaderName<<std::endl;

}

void ResourceManager::renameShaderProgram(const char* oldName, const char* newName)
{
    if (shaderPrograms.find(oldName) == shaderPrograms.end() ||
        shaderPrograms.find(newName) != shaderPrograms.end()) {
        return;
    }

    shaderPrograms[newName] = shaderPrograms[oldName];
    shaderPrograms.erase(oldName);
    std::cout<<"Shader "<<oldName<<" renamed to "<<newName<<std::endl; 
}

void ResourceManager::bindVAO()
{
    glBindVertexArray(VAO);
}

void ResourceManager::bindVBO(float* verticesArray, unsigned int size, int drawingScheme)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, verticesArray, drawingScheme);
}

void ResourceManager::bindEBO(unsigned int* indicesArray, unsigned int size, int drawingScheme)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesArray, drawingScheme);
}



void ResourceManager::clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}




// *******************************
//    PRIVATE METHOD DEFINITIONS
// *******************************


