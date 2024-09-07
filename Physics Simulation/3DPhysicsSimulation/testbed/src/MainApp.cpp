#include "MainApp.hpp"
#include "ShaderActions.hpp"
#include "TextureActions.hpp"



// *******************************
//    PRIVATE METHOD DECLARATIONS 
// *******************************

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, MainApp* mainApp);

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

    glfwSetKeyCallback(_mainWindow, Keyboard::keyCallback);
    
    glfwSetCursorPosCallback(_mainWindow, Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(_mainWindow, Mouse::mouseButtonCallback);
    glfwSetScrollCallback(_mainWindow, Mouse::mouseWheelCallback);

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
    
    // IO init
    mainJ.update();
    if (mainJ.isPresent()) {
        std::cout<<mainJ.getName()<<" is present." <<std::endl;
    }
    else {
        std::cout<<"Joystick not present."<<std::endl;
    }


    return STATE::OKAY;
}

STATE MainApp::run()
{
    _pShaderManager->renameShaderProgram("triangle_left", "left");
    _pShaderManager->renameShaderProgram("triangle_right", "right");

    uint left = _pShaderManager->shaderPrograms["left"];
    uint right = _pShaderManager->shaderPrograms["right"];


    // textures
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
        processInput(_mainWindow, this);

        // Render
        _ResourceManager.clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        // Activate and bind textures to their units
        _pTextureManager->useTexture("usa");   
        _pTextureManager->useTexture("obamna");

        // Draw shapes
        _ResourceManager.bindVAO();
        
        shader::useAndDraw(left, GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        shader::setFloat(left, "mixVal", mixVal);
        shader::setMat4(left, "transform", transform);
        
        shader::useAndDraw(right, GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3*sizeof(float)));
        shader::setFloat(right, "mixVal", mixVal);
        shader::setMat4(right, "transform", transform);
        

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


void processInput(GLFWwindow* window, MainApp* mainApp) 
{
    if (Keyboard::key(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } 

    // change mixVal
    if (Keyboard::key(GLFW_KEY_UP)) {
        mainApp->mixVal = utils::clamp<float>(mainApp->mixVal + 0.05f, 0.0f, 1.0f);
    }
    if (Keyboard::key(GLFW_KEY_DOWN)) {
        mainApp->mixVal = utils::clamp<float>(mainApp->mixVal - 0.05f, 0.0f, 1.0f);
    }

    // translate shader
    if (Keyboard::key(GLFW_KEY_W)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(0.0f, 0.05f, 0.0f));
    }

    if (Keyboard::key(GLFW_KEY_S)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(0.0f, -0.05f, 0.0f));
    }

    if (Keyboard::key(GLFW_KEY_A)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(-0.05f, 0.0f, 0.0f));
    }

    if (Keyboard::key(GLFW_KEY_D)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(0.05f, 0.0f, 0.0f));
    }

    // making the actual shader smaller
    if (Keyboard::key(GLFW_KEY_Q)) {
        if (mainApp->transform[0][0] > 0.01f) {
            mainApp->transform = glm::scale(mainApp->transform, glm::vec3(1-0.01f, 1-0.01f, 0.0f));
        }
    }

    // making the actual shader larger
    if (Keyboard::key(GLFW_KEY_E)) {
        mainApp->transform = glm::scale(mainApp->transform, glm::vec3(1+0.01f, 1+0.01f, 0.0f));
    }

    mainApp->mainJ.update();

}

