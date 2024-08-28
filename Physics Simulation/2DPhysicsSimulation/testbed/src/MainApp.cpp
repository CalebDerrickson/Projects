#include "MainApp.hpp"
#include "ShaderActions.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


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
    _pShaderManager = &_ResourceManager.shaderManager;
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
    _pShaderManager->registerShaderProgram("triangle_left", "triangle", "triangle");
    _pShaderManager->registerShaderProgram("triangle_right", "triangle", "triangle");
    

    // vertex 
    float vertices[] = {
        // positions           // colors            // texture coordinates
        // first triangle
        -0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,    0.5f, 1.0f, 0.75f,   0.0f, 1.0f,
        // second triangle
        0.5f, -0.5f, 0.0f,     0.6f, 1.0, 0.2f,     1.0f, 0.0f,
        0.5f,  0.5f, 0.0f,     1.0f, 0.2f, 1.0f,    1.0f, 1.0f
    };

    uint indices[] = {
        0, 1, 2,
        3, 1, 2
    };
    

    // bind vao
    _ResourceManager.bindVAO();

    // bind vbo
    _ResourceManager.bindVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);

    // set position attribute pointer
    shader::setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));

    // set color attribute pointer
    shader::setAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    // set texture coordinates attribute pointer
    // TODO: Refactor
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // bind ebo
    _ResourceManager.bindEBO(indices, sizeof(indices), GL_STATIC_DRAW);
    
    return STATE::OKAY;
}

STATE MainApp::run()
{
    _pShaderManager->renameShaderProgram("triangle_left", "left");
    _pShaderManager->renameShaderProgram("triangle_right", "right");

    uint left = _pShaderManager->shaderPrograms["left"];
    uint right = _pShaderManager->shaderPrograms["right"];


    // textures
    // TODO: Refactor. Idea is to create a texture struct with a pointer to all modifications. 
    //       the glTexImage2D command is to connect the image to the already binded texture. 

    // texture pipeline:
    //  texture units point to textures
    //  textures point to the actual images in gpu memory
    //  the process is generate texture, then bind texture, then load the data to the texture

    // texture unit -> textures -> image data
    // when we do shader::setInt(...), we are telling the shader to point to whatever texture unit we tell it to

    uint texture1;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // load image
    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../testbed/assets/textures/obamna.jpg", &width, &height, &nChannels, 0); 


    if (data) {
        // loads into GL_TEXTURE0 texture unit. points to texture id, then to the gpu
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        // mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout<<"Failed to load texture!"<<std::endl;
    }

    // Can freely delete data
    stbi_image_free(data);
    shader::useShader(left);
    shader::setInt(left, "texture1", 0);
    // TODO: End Refactor



    while (!glfwWindowShouldClose(_mainWindow)) {
        
        // process input
        processInput(_mainWindow);

        // render
        _ResourceManager.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        // TODO: Refactoring for textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        // TODO: End Refactor


        // draw shapes
        // NOTE: The texture is still bound, so both draw calls will respond to texture1
        _ResourceManager.bindVAO();
        shader::useAndDraw(left, GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        shader::useAndDraw(right, GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(float)));

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

