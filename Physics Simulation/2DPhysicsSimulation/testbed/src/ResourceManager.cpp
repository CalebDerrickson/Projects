#include "ResourceManager.hpp"

// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************
std::string loadShaderSrc(const std::string& filename);




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
    int success;
    char infoLog[512];
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShadersrc = loadShaderSrc(resource_path + "vertex_" + FileName + ".glsl");
    const GLchar* vertShader = vertexShadersrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    // catch error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"Error in vertex shader compilation: "<<std::endl<<infoLog<<std::endl;
    }

    // fragmentShader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShadersrc = loadShaderSrc(resource_path + "fragment_" + FileName + ".glsl");
    const GLchar* fragShader = fragmentShadersrc.c_str();
    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    // catch error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"Error in fragment shader compilation: "<<std::endl<<infoLog<<std::endl;
    }

    // Creating shader programs for linking
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // catch error
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<< "Linking Error:" <<std::endl<<infoLog<<std::endl;
    }

    shaderPrograms[shaderName] = shaderProgram;


    // can delete vertex and frag shader now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout<<"Shader Registered: "<<shaderName<<std::endl;
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

void ResourceManager::setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
{
    
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);

}

void ResourceManager::clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ResourceManager::useAndDraw(const char* shaderProgram, GLenum mode, GLsizei count, GLenum type, const void *indices)
{
    if (shaderPrograms.find(shaderProgram) == shaderPrograms.end()) {
        std::cerr<<"Requested shader program "<<shaderProgram<<" has not been registered. "<<std::endl;
        exit(1);
    }

    glUseProgram(shaderPrograms[shaderProgram]);
    glDrawElements(mode, count, type, indices);
}

// *******************************
//    PRIVATE METHOD DEFINITIONS
// *******************************
std::string loadShaderSrc(const std::string& filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if (!file.is_open()) {
        std::cerr<<"File "<<filename<<"is not open!"<<std::endl;
        exit(1);
    }

    buf << file.rdbuf();
    ret = buf.str();

    file.close(); 
    return ret;
}