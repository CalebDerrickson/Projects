#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <unordered_map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define RESOURCE_PATH "../testbed/assets/"

// TODO: Separate Shaders into classes based on their management and actions upon them. 
// TODO: Add function to register new shader based on different fragment and vertex shaders.
//       i.e. different shaders using the same vertex shader, ...
//       Also, give ability to rename shaders. 


class ResourceManager {
public:

    ResourceManager();
    ~ResourceManager();

    // initializing vao, vbo, ebo
    // TODO: should provide their respective amount?
    void init();

    void registerShaderProgram(const char* shaderName);
    void registerShaderProgram( const char* shaderName, const char* vertexName, const char* fragmentName);
    void renameShaderProgram(const char* oldName, const char* newName);

    void bindVAO();
    void bindVBO(float* verticesArray, unsigned int size, int drawingScheme);
    void bindEBO(unsigned int* indicesArray, unsigned int size, int drawingScheme);


    void clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);


// private:

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // Shader Program map
    std::unordered_map<const char*, unsigned int> shaderPrograms;
};