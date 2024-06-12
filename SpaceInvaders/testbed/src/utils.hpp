#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


typedef enum state{SUCCESS, FAIL} state;

inline void getOpenGLVersion(int* glVersion)
{
    // --Get OpenGL version
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
}