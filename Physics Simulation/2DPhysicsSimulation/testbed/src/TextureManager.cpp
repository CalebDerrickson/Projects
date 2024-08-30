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

    // generate texture
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
    
    // load image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    std::string TexturePath(TEXTURE_PATH);
    std::string TextureName(TexturePath + textureName);
    unsigned char* data = 0;

    // switch on different picture extensions
    switch (fileExtension)
    {
        case FILE_EXTENSION::JPG :
        {
            data = stbi_load((TextureName + ".jpg").c_str(), &width, &height, &nChannels, 0);
            if (data) 
            {        
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            break;
        }
        case FILE_EXTENSION::PNG :
        {
            data = stbi_load((TextureName + ".png").c_str(), &width, &height, &nChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            break;
        }
        case FILE_EXTENSION::UNKNOWN :
        {
            std::cout<<"Unknown File Extension!"<<std::endl;
            break;
        }

        default:    
            break;
    }
    
    if (!data) {
        std::cout<<"Texture failed to load!"<<std::endl;
    }

    // Can freely delete data
    stbi_image_free(data);;
    texturePrograms[textureName.c_str()] = textureRef(textureId, GL_TEXTURE0 + ++nTexturesRegistered); 
    ;
    std::cout<<"Texture registered: "<<textureName<<std::endl;
}

void TextureManager::renameTextureProgram(const char* oldName, const char* newName)
{
    textureRef ref = texturePrograms[oldName];
    texturePrograms.erase(oldName);
    texturePrograms[newName] = ref;
}


void TextureManager::useTexture(const char* name)
{
    textureRef ref = texturePrograms[name];
    glActiveTexture(ref.textureUnit); 
    glBindTexture(GL_TEXTURE_2D, ref.textureId);
}