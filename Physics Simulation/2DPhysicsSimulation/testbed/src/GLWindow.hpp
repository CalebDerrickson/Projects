// Class to manage window initilization and shutdown
#pragma once
#include <stdint.h>
#include <cstdio>
#include "utils.hpp"


class GLWindow{
public:
    GLWindow();
    GLWindow(uint32_t width, uint32_t height, const char* title);
    ~GLWindow();
    
    status init();
    status shutdown();

    uint32_t getWidth() const noexcept {return _width;}
    uint32_t getHeight() const noexcept {return _height;}
    const char* getTitle() const noexcept {return _title;}
    GLFWwindow* getWindow_ptr() {return _window;}
    
private:
    GLFWwindow* _window;
    uint32_t _width;
    uint32_t _height;
    const char* _title;

};