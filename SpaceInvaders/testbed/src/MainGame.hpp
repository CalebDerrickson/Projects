#pragma once
#include "GLWindow.hpp"
#include "utils.hpp"
#include <cstdio>


class MainGame{
public:

    MainGame(uint32_t width, uint32_t height, const char* title);
    ~MainGame();

    void init();
    void run();
    void shutdown();

private:
    GLWindow _glWindow;
    struct state_ptr{Buffer* state_buffer;} state_ptr;    
};

