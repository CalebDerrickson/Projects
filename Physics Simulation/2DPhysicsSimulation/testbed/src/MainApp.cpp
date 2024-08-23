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

// To compile shaders
// TODO: Refactor
std::string loadShaderSrc(const char* filename);

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

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout<<"Using OpenGL version "<< version<<std::endl;

    glViewport(0, 0, _width, _height);

    // Setting window update on resize
    glfwSetFramebufferSizeCallback(_mainWindow, framebufferSizeCallback);

    // Begin Shader Compile
    // One shaderprogram per different colored "thing"
    // For the sake of refactoring, make an array of shaderprograms,
    // maybe a hashtable from "thing" to shaderProgram
    // For each different colored thing, need to modify the offset of the draw command in the main loop

    // TODO: Refactor
    int success;
    char infoLog[512];
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexShadersrc = loadShaderSrc("../testbed/assets/vertex_core.glsl");
    const GLchar* vertShader = vertexShadersrc.c_str();
    glShaderSource(vertexShader, 1, &vertShader, NULL);
    glCompileShader(vertexShader);

    // catch error
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"Error in vertex shader compilation: "<<std::endl<<infoLog<<std::endl;
    }


    // Begin Fragment Compile
    // TODO: Refactor
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentShadersrc = loadShaderSrc("../testbed/assets/fragment_core.glsl");
    const GLchar* fragShader = fragmentShadersrc.c_str();
    glShaderSource(fragmentShader, 1, &fragShader, NULL);
    glCompileShader(fragmentShader);

    // catch error
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<<"Error in fragment shader compilation: "<<std::endl<<infoLog<<std::endl;
    }

    // Creating shader programs for linking
    _shaderProgram = glCreateProgram();

    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    // catch error
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout<< "Linking Error:" <<std::endl<<infoLog<<std::endl;
    }

    // can delete vertex and frag shader now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // # TODO: End Shaders

    // VAO, VBO start
    // TODO: Refactor

    // vertex 
    float vertices[] = {
        // first trangle
        0.5f, 0.5f, 0.0f,   // top right
        -0.5f, 0.5f, 0.0f,  // top left
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f   // bottom right
    };

    unsigned int indices[] = {
      0, 1, 2, // First Triangle 
      2, 3, 0  // Second Triange
    };
    
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    // bind vao
    glBindVertexArray(_VAO);

    // bind vbo
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set attribute pointer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // bind ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // TODO: Done VAO, VBO, EBO


    return STATE::OKAY;
}

STATE MainApp::run()
{

    while (!glfwWindowShouldClose(_mainWindow)) {
        processInput(_mainWindow);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw shapes
        glBindVertexArray(_VAO);
        glUseProgram(_shaderProgram);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

std::string loadShaderSrc(const char* filename)
{
    std::ifstream file;
    std::stringstream buf;

    std::string ret = "";

    file.open(filename);

    if (!file.is_open()) {
        std::cerr<<"File "<<filename<<"is not open!"<<std::endl;
        exit(1);
    }

    buf << file.rdbuf();
    ret = buf.str();

    file.close(); 
    return ret;
}