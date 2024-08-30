// Managing class to handle working with shaders

#pragma once

#include "utils.hpp"
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>





#define TEXTURE_PATH "../testbed/assets/textures/"

struct textureRef{
    uint textureId;
    int textureUnit;
    textureRef() {};
    textureRef(uint textureId_, int textureUnit_) : textureId(textureId_), textureUnit(textureUnit_) {}
};


class TextureManager{
public:

    TextureManager();
    ~TextureManager();

    void registerTextureProgram(const std::string& textureName, FILE_EXTENSION fileExtension, int options[][3], int nOptions);
    void renameTextureProgram(const char* oldName, const char* newName);
    void useTexture(const char* name);
    unsigned int nTexturesRegistered;

    // Texture Program map
    // I know there is no such thing as texturePrograms, but for the sake of
    // consistency in the ResourceManager class I will keep it as
    std::unordered_map<const char*, textureRef> texturePrograms;
};


