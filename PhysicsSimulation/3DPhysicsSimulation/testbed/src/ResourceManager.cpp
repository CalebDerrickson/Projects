#include "ResourceManager.hpp"
#include "Actions/ShaderActions.hpp"

// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************


// *******************************
//    CLASS METHOD DEFINITIONS
// *******************************

ResourceManager::ResourceManager(LinearAllocator& allocator) 
    : Manager(), 
      _linearAllocator(allocator),
      shaderManager(nullptr),
      textureManager(nullptr)
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::init(DynamicAllocator& allocator)
{
    _logger.log(LogLevel::INFO, "Initializing ResourceManager.");
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);  
    shaderManager = new (_linearAllocator.allocate(sizeof(ShaderManager))) ShaderManager(allocator);
    textureManager = new (_linearAllocator.allocate(sizeof(TextureManager))) TextureManager();
    _logger.log(LogLevel::DEBUG, "Initialized ResourceManager.");
}

void ResourceManager::shutdown()
{
    _logger.log(LogLevel::DEBUG, "Shutting Down ResourceManager.");
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void ResourceManager::bindVAO()
{
    glBindVertexArray(VAO);
}

void ResourceManager::bindVBO(float* verticesArray, uint size, int drawingScheme)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, verticesArray, drawingScheme);
}

void ResourceManager::bindEBO(uint* indicesArray, uint size, int drawingScheme)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicesArray, drawingScheme);
}



void ResourceManager::clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}




// *******************************
//    PRIVATE METHOD DEFINITIONS
// *******************************


