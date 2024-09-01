#include "MainApp.hpp"
#include "ShaderActions.hpp"
#include "TextureActions.hpp"



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
    _pTextureManager = &_ResourceManager.textureManager;
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
    
    // Bind VAO, VBO, EBO, and attribute pointers
    _ResourceManager.bindVAO();
    _ResourceManager.bindVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
    shader::setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
    shader::setAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    shader::setAttributePointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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

    // options for texture
    int options[4][3] = {
        {GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT},
        {GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT},
        {GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR},
        {GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST}
    };

    // Register and bind textures
    _pTextureManager->registerTextureProgram("usa", FILE_EXTENSION::PNG, options, 4);
    _pTextureManager->registerTextureProgram("obamna", FILE_EXTENSION::JPG, options, 4);

    // Set the texture units in the shaders
    shader::useShader(left);
    shader::setInt(left, "texture1", _pTextureManager->texturePrograms["obamna"].textureUnit); 
    shader::setInt(left, "texture2", _pTextureManager->texturePrograms["usa"].textureUnit); 
    
    shader::useShader(right);
    shader::setInt(right, "texture1", _pTextureManager->texturePrograms["obamna"].textureUnit); 
    shader::setInt(right, "texture2", _pTextureManager->texturePrograms["usa"].textureUnit); 

    while (!glfwWindowShouldClose(_mainWindow)) {
        // Process input
        processInput(_mainWindow);

        // Render
        _ResourceManager.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        // Activate and bind textures to their units
        _pTextureManager->useTexture("usa");   
        _pTextureManager->useTexture("obamna");

        // Draw shapes
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

