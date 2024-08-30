#include "TextureManager.hpp"


#include <stb_image.h>

TextureManager::TextureManager()
{


}

TextureManager::~TextureManager()
{


}

void TextureManager::registerTextureProgram(const char* textureName, int options[][3], int nOptions)
{
    
    // generate texture
    uint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    for (int i = 0; i < nOptions; i++) {
        int o1 = options[i][0];
        int o2 = options[i][1];
        int o3 = options[i][2];
        glTexParameteri(o1, o2, o3);
    }
    
    // load image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string TexturePath(TEXTURE_PATH);
    std::string TextureName(TexturePath + textureName);
    unsigned char* data = stbi_load((TextureName + ".jpg").c_str(), &width, &height, &nChannels, 0);

    
    if (data) {
        // loads into GL_TEXTURE0 texture unit. points to texture id, then to the gpu
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<<"Failed to load texture!"<<std::endl;
    }

    // Can freely delete data
    stbi_image_free(data);

    texturePrograms[textureName] = textureId; 
    std::cout<<"Texture registered: "<<textureName<<std::endl;
}

void TextureManager::renameTextureProgram(const char* oldName, const char* newName)
{
    uint textureId = texturePrograms[oldName];
    texturePrograms.erase(oldName);
    texturePrograms[newName] = textureId;
}
