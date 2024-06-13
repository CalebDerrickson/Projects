#include "GLWindow.hpp"

GLWindow::GLWindow() :
    _width(800), _height(600), _title("TEMP")
{

}

GLWindow::GLWindow(uint32_t width, uint32_t height, const char* title) :
    _width(width), _height(height), _title(title) 
{
    
}

GLWindow::~GLWindow() 
{
    
}

status GLWindow::init()
{
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // --Create Window
    _window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
    if (!_window) {
        printf("Window failed to be created!\n");
        glfwTerminate();
        return status::FAIL;
    }
    glfwMakeContextCurrent(_window);

    return status::SUCCESS;
}

status GLWindow::shutdown()
{
    if (_window) {
        glfwDestroyWindow(_window);
        return status::SUCCESS;
    }

    return status::FAIL;
}
