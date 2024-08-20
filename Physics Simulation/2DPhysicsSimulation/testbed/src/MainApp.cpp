#include "MainApp.hpp"
#include "../maths/vector_math.hpp"


// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


// *******************************
//    CLASS METHOD DEFINITIONS
// *******************************

MainApp::MainApp(int width, int height, const char* title)
    :   BaseApp(width, height, title)
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
    glViewport(0, 0, _width, _height);

    // Setting window update on resize
    glfwSetFramebufferSizeCallback(_mainWindow, framebufferSizeCallback);
    
    // Test for math library and structuring of makefile
    // TODO: Remove this
    vec3<int> vec = {3, 2, 1};
    vec3<int> temp = vec+=3;

    std::cout<<"vec: " <<vec.x<<' '<<vec.y<<' '<<vec.z<<std::endl;
    std::cout<<"temp: " <<temp.x<<' '<<temp.y<<' '<<temp.z<<std::endl;
    
    vec = temp - vec;
    std::cout<<"vec: " <<vec.x<<' '<<vec.y<<' '<<vec.z<<std::endl;
    


    return STATE::OKAY;
}

STATE MainApp::run()
{

    while (!glfwWindowShouldClose(_mainWindow)) {
        processInput(_mainWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

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