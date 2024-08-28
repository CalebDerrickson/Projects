#pragma once

#define RESOURCE_PATH "../testbed/assets/"

#include "ShaderManager.hpp"


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

    void bindVAO();
    void bindVBO(float* verticesArray, unsigned int size, int drawingScheme);
    void bindEBO(unsigned int* indicesArray, unsigned int size, int drawingScheme);


    void clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);


// private:

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    ShaderManager shaderManager;

};