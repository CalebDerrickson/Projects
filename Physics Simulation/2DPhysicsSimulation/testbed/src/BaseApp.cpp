#include "BaseApp.hpp"

// Definition of the static member
int BaseApp::_isInitialized = false;

BaseApp::BaseApp(uint32_t width, uint32_t height, const char* title)
    : _width(width), _height(height), _title(title)
{
    _isInitialized = SIM_NO;

}

BaseApp::~BaseApp()
{


}

STATE BaseApp::init()
{
    if (_isInitialized == SIM_YES) {
        // Don't want to initialize twice
        return STATE::OKAY;
    } 

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Initialize the window
    _mainWindow = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (_mainWindow == nullptr) {
        std::cout<<"Could not create window!" << std::endl;
        glfwTerminate();
        return STATE::ERROR;
    }
    
    glfwMakeContextCurrent(_mainWindow);
    // Might require the window to be instanciated
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout<<"Failed to initialize glad!" << std::endl;
            glfwTerminate();
            return STATE::ERROR;
    }

    _isInitialized = SIM_YES;
//     std::cout<<"init"<<std::endl;
    return STATE::OKAY;
}


STATE BaseApp::shutdown()
{

    glfwTerminate();
    return STATE::OKAY;
}

