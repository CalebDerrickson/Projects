#pragma once
#include "BaseApp.hpp"

class MainApp : public BaseApp
{
public:
    MainApp(int width, int height, const char* title);
    ~MainApp();

    STATE init() override;
    STATE run() override;
    STATE shutdown() override;

private:
    // window pointer is provided by the BaseApp class

    // TODO: refactor this
    unsigned int _VAO;
    unsigned int _VBO;
    unsigned int _EBO;
    unsigned int _shaderProgram;

};