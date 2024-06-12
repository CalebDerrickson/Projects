#include "MainGame.hpp"

// PRIVATE DECLARATIONS
void error_callback(int error, const char* description);

// CLASS DEFINITIONS
MainGame::MainGame(uint32_t width, uint32_t height, const char* title) :
    _glWindow (GLWindow(width, height, title))
{
    

}

MainGame::~MainGame()
{


}

void MainGame::init()
{
    glfwSetErrorCallback(error_callback);

    if (glfwInit() == GLFW_FALSE) {printf("ERROR\n"); return;}

    // --Create Window
    if (_glWindow.init() == state::FAIL) {return;} 
    
    // --Initialize GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW.\n");
        glfwTerminate();
        return;
    }

    int glVersion[2] = {-1, -1};
    getOpenGLVersion(glVersion);

    printf("Using OpenGL v%d.%d\n", glVersion[0], glVersion[1]);
}

void MainGame::run()
{
    // -Game Loop
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    
    while (!glfwWindowShouldClose(_glWindow.getWindow_ptr())) {
        
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(_glWindow.getWindow_ptr());

        glfwPollEvents();
    }

}

void MainGame::shutdown()
{
    _glWindow.shutdown(); 
    
    
    glfwTerminate();

}


// PRIVATE DEFINITIONS
void error_callback(int error, const char* description) 
{
    fprintf(stderr, "Error: %s\n", description);
}
