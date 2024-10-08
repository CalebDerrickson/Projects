#pragma once
#include "BaseApp.hpp"
#include "ResourceManager.hpp"
#include "Logger.hpp"
#include "memory/LinearAllocator.hpp"
#include "memory/DynamicAllocator.hpp"

#include "io/Keyboard.hpp"
#include "io/Mouse.hpp"
#include "io/Joystick.hpp"

class MainApp : public BaseApp
{
public:
    MainApp(int width, int height, const char* title);
    ~MainApp();

    STATE init() override;
    STATE run() override;
    STATE shutdown() override;

    glm::mat4 transform = glm::mat4(1.0f);
    Joystick mainJ = Joystick(0);

    float mixVal = 0.5f;

    float x;
    float y;
    float z;
    glm::vec3 dir;
    int spin;

private:
    // window pointer is provided by the BaseApp class

    LinearAllocator _linearAllocator;
    DynamicAllocator _dynamicAllocator;

    ResourceManager* _ResourceManager;

    // Pointers to _ResourceManager's managers for ease of access
    ShaderManager* _pShaderManager;
    TextureManager* _pTextureManager;
    
    Logger& _logger;
};