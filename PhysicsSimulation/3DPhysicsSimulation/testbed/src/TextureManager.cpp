#include "TextureManager.hpp"
#include "Actions/TextureActions.hpp"

#include <stb_image.h>

TextureManager::TextureManager()
    : Manager()
{
    nTexturesRegistered = 0;

}

TextureManager::~TextureManager()
{


}

void TextureManager::registerTextureProgram(const std::string& textureName, FILE_EXTENSION fileExtension, int options[][3], int nOptions)
{
    _logger.logf(LogLevel::DEBUG, "Registering Texture: %s", textureName);
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
            _logger.log(LogLevel::ERROR, "Unknown file extension!");
            return;
    }
    
    if (!data) {
        _logger.log(LogLevel::ERROR, "Texture failed to load!");
        return;
    }

    GLenum format = (fileExtension == FILE_EXTENSION::PNG) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);
    
    // Store texture ID and texture unit
    texturePrograms[textureName.c_str()] = textureRef(textureId, nTexturesRegistered);
    
    _logger.logf(LogLevel::DEBUG, "Texture Registered: %s", textureName);
    _logger.logf(LogLevel::TRACE, "TextureId: %llu.", textureId);
    _logger.logf(LogLevel::TRACE, "Texture Location: %p", &texturePrograms[textureName.c_str()]);
    nTexturesRegistered++;
    _logger.logf(LogLevel::TRACE, "Number of Registered Textures: %llu", nTexturesRegistered);
}


void TextureManager::renameTextureProgram(const char* oldName, const char* newName)
{
    _logger.logf(LogLevel::DEBUG, "Renaming texture: %s", oldName);
    
    auto it = texturePrograms.find(oldName);
    if (it == texturePrograms.end()) {
        _logger.logf(LogLevel::ERROR, "Texture not found: %s", oldName);
        return;
    }
    it = texturePrograms.find(newName);
    if (it != texturePrograms.end()) {
        _logger.logf(LogLevel::ERROR, "Texture name %s already has a texture!", newName);
        return;
    }


    textureRef ref = texturePrograms[oldName];
    texturePrograms.erase(oldName);
    texturePrograms[newName] = ref;
    _logger.logf(LogLevel::DEBUG, "Texture %s renamed to", oldName, newName);
    
}


void TextureManager::useTexture(const std::string& textureName) {
    auto it = texturePrograms.find(textureName);
    if (it == texturePrograms.end()) {
        _logger.logf(LogLevel::WARN, "Texture %s not found! Cannot be used.", textureName);
        return;
    }

    glActiveTexture(GL_TEXTURE0 + it->second.textureUnit);
    glBindTexture(GL_TEXTURE_2D, it->second.textureId);
    // _logger.logf(LogLevel::TRACE, "Using texture: %llu", it->second.textureUnit);
}