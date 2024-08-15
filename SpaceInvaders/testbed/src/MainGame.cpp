#include "MainGame.hpp"

// PRIVATE DECLARATIONS


// CLASS DEFINITIONS
MainGame::MainGame(uint32_t width, uint32_t height, const char* title) :
    _glWindow (GLWindow(width, height, title))
{
    state_ptr.state_buffer = new Buffer();
    state_ptr.state_buffer->height = height;
    state_ptr.state_buffer->width = width;
    


}

MainGame::~MainGame()
{


}

void MainGame::init()
{

    // --Create Window
    if (_glWindow.init() == status::FAIL) {return;} 
    
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

    // --Init state buffer
    const int width = state_ptr.state_buffer->width; 
    const int height = state_ptr.state_buffer->height; 

    state_ptr.state_buffer->data = new uint32_t[width * height];
    uint32_t clear_color = rgb_to_uint32(0, 0, 0);
    buffer_clear(state_ptr.state_buffer, clear_color);

    // Create texture for presenting buffer to OpenGL
    GLuint buffer_texture;
    glGenTextures(1, &buffer_texture);
    glBindTexture(GL_TEXTURE_2D, buffer_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, state_ptr.state_buffer->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    
    // vertex array object (VAO) to tell we're drawing three vertices
    GLuint fullscreen_triangle_vao;
    glGenVertexArrays(1, &fullscreen_triangle_vao);

    // --Vertex Shader
    const char* vertex_shader =
    "\n"
    "#version 330\n"
    "\n"
    "noperspective out vec2 TexCoord;\n"
    "\n"
    "void main(void){\n"
    "\n"
    "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
    "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
    "    \n"
    "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
    "}\n";

    const char* fragment_shader =
    "\n"
    "#version 330\n"
    "\n"
    "uniform sampler2D buffer;\n"
    "noperspective in vec2 TexCoord;\n"
    "\n"
    "out vec3 outColor;\n"
    "\n"
    "void main(void){\n"
    "    outColor = texture(buffer, TexCoord).rgb;\n"
    "}\n";

    GLuint shader_id = glCreateProgram();

    // -- Create the vertex shader
    {
        GLuint shader_vp = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(shader_vp, 1, &vertex_shader, 0);
        glCompileShader(shader_vp);
        validate_shader(shader_vp, vertex_shader);
        glAttachShader(shader_id, shader_vp);

        glDeleteShader(shader_vp);
    }

    // -- Create the fragment shader
    {
        GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
        
        glShaderSource(shader_fp, 1, &fragment_shader, 0);
        glCompileShader(shader_fp);
        validate_shader(shader_fp, fragment_shader);
        glAttachShader(shader_id, shader_fp);

        glDeleteShader(shader_fp);
    }

    glLinkProgram(shader_id);

    if (!validate_program(shader_id)) 
    {
        fprintf(stderr, "Error while validating shader.\n");
        glfwTerminate();
        glDeleteVertexArrays(1, &fullscreen_triangle_vao);
        delete[] state_ptr.state_buffer->data;
        return;
    }

    glUseProgram(shader_id);

    // Now attach the texture to the uniform sampler2D in the fragment shader.
    GLint location = glGetUniformLocation(shader_id, "buffer");
    glUniform1i(location, 0);

    // OpenGL setup
    glDisable(GL_DEPTH_TEST); // Disabling depth testing 
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(fullscreen_triangle_vao); // Bind to vertex array 
    

    // Game initialization
    _game.width = width;
    _game.height = height;
    _game.num_aliens = 55;
    _game.aliens = new Alien[_game.num_aliens];
    _game.player.x = width / 2 - 5;
    _game.player.y = height / 15;
    _game.player.life = 3;

    

    // intialize alien locations
    for (int y_i = 0; y_i < 5; y_i++) {
        for (int x_i = 0; x_i < 11; x_i++) {
            _game.aliens[y_i * 11 + x_i].x = 16 * x_i + 20;
            _game.aliens[y_i * 11 + x_i].y = 17 * y_i + 128;
        }
    }
    


}

void MainGame::run()
{
    // -Game Loop
    uint32_t clear_color = rgb_to_uint32(0, 128, 0);
    Sprite alien_sprite;
    Sprite player_sprite;
    create_alien_sprite(alien_sprite);
    create_player_sprite(player_sprite);

    while (!glfwWindowShouldClose(_glWindow.getWindow_ptr()))
    {

        buffer_clear(state_ptr.state_buffer, clear_color);

        // Draw aliens
        for (size_t ai = 0; ai < _game.num_aliens; ai++) {
            const Alien& alien = _game.aliens[ai];
            buffer_sprite_draw(state_ptr.state_buffer, alien_sprite,
            alien.x, alien.y, rgb_to_uint32(128, 0, 0));
        }

        // Draw player
        buffer_sprite_draw(state_ptr.state_buffer, player_sprite, 
        _game.player.x, _game.player.y, rgb_to_uint32(128, 0, 0));

        glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0,
            state_ptr.state_buffer->width, state_ptr.state_buffer->height,
            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
            state_ptr.state_buffer->data
        );
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(_glWindow.getWindow_ptr());

        glfwPollEvents();

    }
}

void MainGame::shutdown()
{
    _glWindow.shutdown(); 
    


    // Error: The GLFW library is not initialized ?
    glfwTerminate();

    delete _game.aliens;

}


// PRIVATE DEFINITIONS
