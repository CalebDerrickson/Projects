#include "MainApp.hpp"

// # TODO: Temporary
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#if 0
    // Here for the sake of remembering I have this.
    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>
#endif
// # TODO: End Temporary

// To compile shader/fragment programs
// TODO: Refactor this
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>



// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// *******************************
//    CLASS METHOD DEFINITIONS
// *******************************

MainApp::MainApp(int width, int height, const char* title)
    :   BaseApp(width, height, title),
        _ResourceManager()
{

}

MainApp::~MainApp()
{


}

STATE MainApp::init()
{
    // Initialize the basic stuff, like glfw and glad
    // Also initializes _mainWindow
    if (BaseApp::init() == STATE::ERROR) {
        std::cout<<"Error in initialization"<<std::endl;
        return STATE::ERROR;
    }

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout<<"Using OpenGL version "<< version<<std::endl;

    glViewport(0, 0, _width, _height);

    // Setting window update on resize
    glfwSetFramebufferSizeCallback(_mainWindow, framebufferSizeCallback);
    

    _ResourceManager.init();
    _ResourceManager.registerShaderProgram("triangle_left");
    _ResourceManager.registerShaderProgram("triangle_right");
    

    // vertex 
    float vertices[] = {
        // first trangle
        -0.5, 0.5, 0.0,  // top left
        -0.5, -0.5, 0.0, // bottom left
        0.3, 0.5, 0.0, // top right

        // second triangle
        0.5, 0.5, 0.0, // top right
        -0.3, -0.5, 0.0, // bottom left
        0.5, -0.5, 0.0 // bottom right
    };

    unsigned int indices[] = {
      0, 1, 2, // First Triangle 
      3, 4, 5  // Second Triange
    };
    

    // bind vao
    _ResourceManager.bindVAO();

    // bind vbo
    _ResourceManager.bindVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

    // set attribute pointer 
    _ResourceManager.setAttributePointer();

    // bind ebo
    _ResourceManager.bindEBO(indices, sizeof(indices), GL_STATIC_DRAW);
    
    return STATE::OKAY;
}

STATE MainApp::run()
{

    while (!glfwWindowShouldClose(_mainWindow)) {
        processInput(_mainWindow);
        _ResourceManager.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);
        
        _ResourceManager.bindVAO();

        // draw shapes
        _ResourceManager.useAndDraw("triangle_left", GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        _ResourceManager.useAndDraw("triangle_right", GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(float)));


        glfwSwapBuffers(_mainWindow);
        glfwPollEvents();
    } 

    return STATE::OKAY;
}

STATE MainApp::shutdown()
{
    (void)BaseApp::shutdown();

    return STATE::OKAY;
}


// *******************************
//    PRIVATE METHOD DEFINITIONS
// *******************************


void framebufferSizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } 
}

