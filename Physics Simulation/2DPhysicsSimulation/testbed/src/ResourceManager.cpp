#include "ResourceManager.hpp"

// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************
std::string loadShaderSrc(const std::string& filename);
GLuint compileShader(const std::string& filePath, GLenum type);



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
    unsigned int vertexShader = compileShader(resource_path + "vertex_" + FileName + ".glsl", GL_VERTEX_SHADER);

    // fragmentShader
    unsigned int fragmentShader = compileShader(resource_path + "fragment_" + FileName + ".glsl", GL_FRAGMENT_SHADER);
    

    // Creating shader programs for linking
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // catch error
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout<< "Linking Error:" <<std::endl<<infoLog<<std::endl;
        exit(1);
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
    useShader(shaderProgram);
    glDrawElements(mode, count, type, indices);
}

void ResourceManager::useShader(const char* shaderProgram) 
{
    if (shaderPrograms.find(shaderProgram) == shaderPrograms.end()) {
        std::cerr<<"Requested shader program "<<shaderProgram<<" has not been registered. "<<std::endl;
        exit(1);
    }

    GLint current = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &current);
    if (shaderPrograms[shaderProgram] == current) return;

    glUseProgram(shaderPrograms[shaderProgram]);
}

void ResourceManager::setMat4(const char* shaderProgram, const char* name, glm::mat4 val)
{
    if (shaderPrograms.find(shaderProgram) == shaderPrograms.end()) {
        std::cerr<<"Requested shader program "<<shaderProgram<<" has not been registered. "<<std::endl;
        exit(1);
    }

    glUniformMatrix4fv(glGetUniformLocation(shaderPrograms[shaderProgram], name), 1, GL_FALSE, glm::value_ptr(val));
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

GLuint compileShader(const std::string& filePath, GLenum type)
{

    int success;
    char infoLog[512];

    GLuint ret  = glCreateShader(type);
    std::string shaderSrc = loadShaderSrc(filePath);
    const GLchar* shader = shaderSrc.c_str();
    glShaderSource(ret, 1, &shader, NULL);
    glCompileShader(ret);

    glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(ret, 512, NULL, infoLog);
        std::cout<<"Error in shader compilation: "<<std::endl<<infoLog<<std::endl;
        exit(1);
    }
    
    return ret;
}
