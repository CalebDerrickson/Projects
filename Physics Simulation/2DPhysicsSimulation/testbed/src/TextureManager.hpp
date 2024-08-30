// Managing class to handle working with shaders

#pragma once

#include "utils.hpp"
#include <unordered_map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>





#define TEXTURE_PATH "../testbed/assets/textures/"

// struct textureRef{
//     uint id;
// };


class TextureManager{
public:

    TextureManager();
    ~TextureManager();

    void registerTextureProgram(const char* textureName, int options[][3], int nOptions);
    void renameTextureProgram(const char* oldName, const char* newName);

    // Texture Program map
    // I know there is no such thing as texturePrograms, but for the sake of
    // consistency in the ResourceManager class I will keep it as
    std::unordered_map<const char*, uint> texturePrograms;
};


