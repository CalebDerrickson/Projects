#pragma once

#define RESOURCE_PATH "../testbed/assets/"

#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "utils.hpp"

class ResourceManager {
public:

    ResourceManager();
    ~ResourceManager();

    // initializing vao, vbo, ebo
    // TODO: should provide their respective amount?
    void init();

    void bindVAO();
    void bindVBO(float* verticesArray, uint size, int drawingScheme);
    void bindEBO(uint* indicesArray, uint size, int drawingScheme);


    void clearScreen(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);


// private:

    uint VAO;
    uint VBO;
    uint EBO;

    ShaderManager shaderManager;
    TextureManager textureManager;
};