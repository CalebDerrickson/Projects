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
        _linearAllocator(10* KB),
        _dynamicAllocator(5* KB)
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

    glViewport(0, 0, _screenWidth, _screenHeight);

    // Setting window update on resize
    glfwSetFramebufferSizeCallback(_mainWindow, framebufferSizeCallback);

    glfwSetKeyCallback(_mainWindow, Keyboard::keyCallback);
    
    glfwSetCursorPosCallback(_mainWindow, Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(_mainWindow, Mouse::mouseButtonCallback);
    glfwSetScrollCallback(_mainWindow, Mouse::mouseWheelCallback);

    // Enables Depth testing. Also needs to be updated in the main loop
    glEnable(GL_DEPTH_TEST);

    // linear allocator init. Initialize with 10k bytes. 
    
    

    // Resource Manager Init
    _ResourceManager = new (_linearAllocator.allocate(sizeof(ResourceManager))) ResourceManager(_linearAllocator);
    _ResourceManager->init(_dynamicAllocator);
    _pShaderManager = _ResourceManager->shaderManager;
    _pTextureManager = _ResourceManager->textureManager;


    // shader programs
    _pShaderManager->registerShaderProgram("cube_left", "cube", "cube");
    _pShaderManager->registerShaderProgram("cube_right", "cube", "cube");
    

    // shader objects
    // want to just throw the names of the shaderprograms to register shader
    std::vector<std::string> shaderProgramNames = {"cube_left", "cube_right"};
    _pShaderManager->registerShader("cube", shaderProgramNames);


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

    Shader* shader_cube = _pShaderManager->shaderMap["cube"];
    shader::setInt(shader_cube, "texture1", _pTextureManager->texturePrograms["obamna"].textureUnit);
    shader::setInt(shader_cube, "texture2", _pTextureManager->texturePrograms["usa"].textureUnit); 

    // vertices for cube
float vertices[] = {
    // Position           // Texture
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
    
    // Bind VAO, VBO, EBO, and attribute pointers
    _ResourceManager->bindVAO();
    _ResourceManager->bindVBO(vertices, sizeof(vertices), GL_STATIC_DRAW);
    shader::setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
    
    // No Color attribute (for now)
    // shader::setAttributePointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    
    
    shader::setAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    // Using VAO (for now)
    // _ResourceManager.bindEBO(indices, sizeof(indices), GL_STATIC_DRAW); 
    
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

    Shader* shader_cube = _pShaderManager->shaderMap["cube"];

    x = 0.0f;
    y = 0.0f;
    z = 3.0f;
    dir = glm::vec3(0.0f);
    spin = 0;
    glm::mat4 rotation = glm::mat4(1.0f);
    
    while (!glfwWindowShouldClose(_mainWindow)) {
        // Process input
        processInput(_mainWindow, this);

        // Render
        _ResourceManager->clearScreen(0.2f, 0.3f, 0.3f, 1.0f);

        // Activate and bind textures to their units
        _pTextureManager->useTexture("usa");   
        _pTextureManager->useTexture("obamna");

        // Draw shapes
        _ResourceManager->bindVAO();

        // create transformation for screen 
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0F);

        if (spin == 0) {
            model = rotation;
        }
        else {
            float angle = glm::radians(1.0f);
            glm::mat4 deltaRotation = glm::rotate(glm::mat4(1.0f), angle, dir);

            // Accumulate the rotation on the current rotation matrix
            rotation = deltaRotation * rotation;  // Update the orientation
            model = rotation;
        }

        model = rotation;
        view = glm::translate(view, glm::vec3(-x, -y, -z));
        projection = glm::perspective(glm::radians(45.0f), (float)(_screenWidth) / (float)_screenHeight, 0.1f, 100.0f);

        // Just drawing the Cube
        glDrawArrays(GL_TRIANGLES, 0, 36); 

        shader::setFloat(shader_cube, "mixVal", mixVal);        

        // setting mats for camera
        shader::setMat4(shader_cube, "model", model);
        shader::setMat4(shader_cube, "view", view);
        shader::setMat4(shader_cube, "projection", projection);           

        glfwSwapBuffers(_mainWindow);
        glfwPollEvents();
    }
    return STATE::OKAY;
}

STATE MainApp::shutdown()
{
    _ResourceManager->shutdown();
    (void)BaseApp::shutdown();
    
    return STATE::OKAY;
}


// *******************************
//    PRIVATE METHOD DEFINITIONS
// *******************************


void framebufferSizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
    // may need to update width and height?
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
        mainApp->y -= 0.05f;
    }

    if (Keyboard::key(GLFW_KEY_S)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(0.0f, -0.05f, 0.0f));
        mainApp->y += 0.05f;
    }

    if (Keyboard::key(GLFW_KEY_A)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(-0.05f, 0.0f, 0.0f));
        mainApp->x += 0.05f;
    }

    if (Keyboard::key(GLFW_KEY_D)) {
        mainApp->transform = glm::translate(mainApp->transform, glm::vec3(0.05f, 0.0f, 0.0f));
        mainApp->x -= 0.05f;
    }

    // making the actual shader smaller
    if (Keyboard::key(GLFW_KEY_Q)) {
        if (mainApp->transform[0][0] > 0.01f) {
            mainApp->transform = glm::scale(mainApp->transform, glm::vec3(1-0.01f, 1-0.01f, 0.0f));
        }
        mainApp->z += 0.05f;
        
    }

    // making the actual shader larger
    if (Keyboard::key(GLFW_KEY_E)) {
        mainApp->transform = glm::scale(mainApp->transform, glm::vec3(1+0.01f, 1+0.01f, 0.0f));
        
        if (mainApp->z > 0.01f) {
            mainApp->z -=0.05f;
        }
    }

    if (Keyboard::key(GLFW_KEY_KP_8)) {
        mainApp->dir = glm::vec3(1.0f, 0.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_9)) {
        mainApp->dir = glm::vec3(1.0f, -1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_6)) {
        mainApp->dir = glm::vec3(0.0f, -1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_3)) {
        mainApp->dir = glm::vec3(-1.0f, -1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_2)) {
        mainApp->dir = glm::vec3(-1.0f, 0.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_1)) {
        mainApp->dir = glm::vec3(-1.0f, 1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_4)) {
        mainApp->dir = glm::vec3(0.0f, 1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_7)) {
        mainApp->dir = glm::vec3(1.0f, 1.0f, 0.0f);
        mainApp->spin = 1;
    } else
    if (Keyboard::key(GLFW_KEY_KP_5)) {
        mainApp->spin = 0;
    }
    
    mainApp->dir = glm::normalize(mainApp->dir);
    
    mainApp->mainJ.update();

}

