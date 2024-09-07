#pragma once
#include "BaseApp.hpp"
#include "ResourceManager.hpp"

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


private:
    // window pointer is provided by the BaseApp class

    ResourceManager _ResourceManager;

    // Pointer to _ResourceManager's shaderManager for ease of access
    ShaderManager* _pShaderManager;
    TextureManager* _pTextureManager;
};