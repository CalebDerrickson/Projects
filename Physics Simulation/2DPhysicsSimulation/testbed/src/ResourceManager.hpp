#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <unordered_map>

#define RESOURCE_PATH "../testbed/assets/"

class ResourceManager {
public:

    ResourceManager();
    ~ResourceManager();

    // initializing vao, vbo, ebo
    // TODO: should provide their respective amount?
    void init();

    void registerShaderProgram(const char* shaderName);

    void bindVAO();
    void bindVBO(float* verticesArray, unsigned int size, int drawingScheme);
    void bindEBO(unsigned int* indicesArray, unsigned int size, int drawingScheme);

    // TODO: I don't know what this does. Fixed feature right now.  
    void setAttributePointer();

    void clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    void useAndDraw(const char* shaderProgram, GLenum mode, GLsizei count, GLenum type, const void *indices);

// private:

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    // Shader Program map
    std::unordered_map<const char*, unsigned int> shaderPrograms;
};