#include "test/HelloWorld.hpp"
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description) 
{
    fprintf(stderr, "Error: %s\n", description);
}


int main() {
    // -Initialization
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {return -1;}
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // --Create Window
    GLFWwindow* window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // --Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return -1;
    }

    // --Get OpenGL version
    int glVersion[2] = {-1, -1};
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);

    printf("Using OpenGL v%d.%d\n", glVersion[0], glVersion[1]);

    // -Game Loop
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // -Terminate 
    glfwDestroyWindow(window);
    glfwTerminate();

}