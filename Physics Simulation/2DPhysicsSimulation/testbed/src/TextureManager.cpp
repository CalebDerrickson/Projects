#include "TextureManager.hpp"
#include "TextureActions.hpp"

#include <stb_image.h>

TextureManager::TextureManager()
{
    nTexturesRegistered = 0;

}

TextureManager::~TextureManager()
{


}

void TextureManager::registerTextureProgram(const std::string& textureName, FILE_EXTENSION fileExtension, int options[][3], int nOptions)
{
    // Generate texture
    uint textureId;
    glGenTextures(1, &textureId);
    glActiveTexture(GL_TEXTURE0 + nTexturesRegistered);
    glBindTexture(GL_TEXTURE_2D, textureId);

    for (int i = 0; i < nOptions; i++) {
        int o1 = options[i][0];
        int o2 = options[i][1];
        int o3 = options[i][2];
        glTexParameteri(o1, o2, o3);
    }
    
    // Load image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string TexturePath(TEXTURE_PATH);
    std::string TextureName(TexturePath + textureName);
    unsigned char* data = 0;

    // Switch on different picture extensions
    switch (fileExtension)
    {
        case FILE_EXTENSION::JPG :
            data = stbi_load((TextureName + ".jpg").c_str(), &width, &height, &nChannels, 0);
            break;
        case FILE_EXTENSION::PNG :
            data = stbi_load((TextureName + ".png").c_str(), &width, &height, &nChannels, 0);
            break;
        default:
            std::cout << "Unknown File Extension!" << std::endl;
            return;
    }
    
    if (!data) {
        std::cout << "Texture failed to load!" << std::endl;
        return;
    }

    GLenum format = (fileExtension == FILE_EXTENSION::PNG) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    // Store texture ID and texture unit
    texturePrograms[textureName.c_str()] = textureRef(textureId, nTexturesRegistered);
    std::cout << "Texture registered: " << textureName <<' '<<textureId<<' '<<nTexturesRegistered<<std::endl;
    std::cout << "Address of textureRef for " << textureName << ": " << &texturePrograms[textureName.c_str()] << std::endl;
    nTexturesRegistered++;
}


void TextureManager::renameTextureProgram(const char* oldName, const char* newName)
{
    textureRef ref = texturePrograms[oldName];
    texturePrograms.erase(oldName);
    texturePrograms[newName] = ref;
}


void TextureManager::useTexture(const std::string& textureName) {
    auto it = texturePrograms.find(textureName);
    if (it == texturePrograms.end()) {
        std::cout << "Texture " << textureName << " not found!" << std::endl;
        return;
    }

    glActiveTexture(GL_TEXTURE0 + it->second.textureUnit);
    glBindTexture(GL_TEXTURE_2D, it->second.textureId);

}