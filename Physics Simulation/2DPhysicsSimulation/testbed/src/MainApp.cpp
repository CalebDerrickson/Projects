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
        // positions           // colors
        // first triangle
        -0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.5f, 
        0.15f, -0.0f, 0.0f,    0.5f, 1.0f, 0.75f,
        // second triangle
        0.0f, 0.5f, 0.0f,      0.6f, 1.0, 0.2f,
        0.5f, -0.4f, 0.0f,     1.0f, 0.2f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 
        3, 1, 2
    };
    

    // bind vao
    _ResourceManager.bindVAO();

    // bind vbo
    _ResourceManager.bindVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

    // set position attribute pointer
    _ResourceManager.setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

    // set color attribute pointer
    _ResourceManager.setAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    // bind ebo
    _ResourceManager.bindEBO(indices, sizeof(indices), GL_STATIC_DRAW);
    
    return STATE::OKAY;
}

STATE MainApp::run()
{

    // TODO: Abstract to resource manager
    // TODO (priority 1) should be delayed until resource manager todo has been done.  
    // shader 1
    glm::mat4 trans(1.0f);
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    _ResourceManager.useShader("triangle_left");
    _ResourceManager.setMat4("triangle_left", "transform", trans);
    
    // shader 2
    _ResourceManager.useShader("triangle_right");
    _ResourceManager.setMat4("triangle_right", "transform", trans);

    while (!glfwWindowShouldClose(_mainWindow)) {
        
        // process input
        processInput(_mainWindow);

        // render
        _ResourceManager.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);
        
        // update rotation
        // reset matrix (has different values)
        trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 50.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        // shader1
        _ResourceManager.useShader("triangle_left");
        _ResourceManager.setMat4("triangle_left", "transform", trans);

        // shader2
        _ResourceManager.useShader("triangle_right");
        _ResourceManager.setMat4("triangle_right", "transform", trans);


        // draw shapes
        _ResourceManager.bindVAO();
        _ResourceManager.useAndDraw("triangle_left", GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        _ResourceManager.useAndDraw("triangle_right", GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(float)));

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

