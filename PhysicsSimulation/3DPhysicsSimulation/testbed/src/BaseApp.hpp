#pragma once
#include <stdint.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"



class BaseApp
{
public:

    
    BaseApp(uint32_t width, uint32_t height, const char* title);
    ~BaseApp();

    virtual STATE init();

    // Since BaseApp will not instantiate the window, run will be purely virtual
    virtual STATE run() = 0;
    virtual STATE shutdown();

    
protected:
    
    uint32_t _screenWidth;
    uint32_t _screenHeight;
    const char* _title;

    // glad requires a context window for initialization
    GLFWwindow* _mainWindow = nullptr;

private:
    static int _isInitialized; // Keep track of initialization 

};
