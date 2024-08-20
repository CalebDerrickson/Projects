#include "MainApp.hpp"

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
    // Initialize the basic stuff, like glfw
    BaseApp::init();
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Initialize the window
    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (_window == nullptr) {
        std::cout<<"Could not create window!" << std::endl;
        glfwTerminate();
        return STATE::ERROR;
    }
    
    glfwMakeContextCurrent(_window);
    // Might require the window to be instanciated
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout<<"Failed to initialize glad!" << std::endl;
            glfwTerminate();
            return STATE::ERROR;
        }


    
    glViewport(0, 0, 800, 600);

    // Setting window update on resize
    glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);



    return STATE::OKAY;
}

STATE MainApp::run()
{

    while (!glfwWindowShouldClose(_window)) {
        processInput(_window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(_window);
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