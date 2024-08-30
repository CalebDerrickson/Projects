#include "utils.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace textures{

    void useTexture(uint textureId)
    {
        glActiveTexture(GL_TEXTURE0 + textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

};