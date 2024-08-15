#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


typedef enum status{SUCCESS, FAIL} status;

inline void getOpenGLVersion(int* glVersion)
{
    // --Get OpenGL version
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
}

inline uint32_t rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b) 
{
    // left-most 24 bits are for the r, g, b values
    // the remaining bits are left to the alpha value,
    // which is set to 255. 
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

// NEW STUFF, DON'T KNOW WHERE TO PUT

struct Buffer
{
    size_t width, height;
    uint32_t *data;
};

struct Sprite
{
    size_t width, height;
    uint8_t* data;
};

struct Alien 
{
    size_t x, y;
    uint8_t type;
};

struct Player
{
    size_t x, y;
    size_t life;
};

struct Game 
{
    size_t width, height;
    size_t num_aliens;
    Alien* aliens;
    Player player;  
};

inline void buffer_clear(Buffer* buffer, uint32_t color) 
{
    for (size_t i = 0; i < buffer->width * buffer->height; i++) {
        buffer->data[i] = color;
    }
}


inline void validate_shader(GLuint shader, const char* file = 0)
{
    static const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if (length > 0) {
        printf("Shader %d(%s) compile error: %s\n",
        shader, (file ? file : ""), buffer);
    } 
}

inline bool validate_program(GLuint program) 
{
    static const GLsizei BUFFER_SIZE = 512;
    GLchar buffer[BUFFER_SIZE];
    GLsizei length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if (length > 0) {
        printf("Program %d link error: %s\n", program, buffer);
        return false;
    }

    return true;
}

inline void buffer_sprite_draw(
    Buffer* buffer, const Sprite& sprite,
    size_t x, size_t y, uint32_t color
){
    for(size_t xi = 0; xi < sprite.width; ++xi)
    {
        for(size_t yi = 0; yi < sprite.height; ++yi)
        {
            size_t sy = sprite.height - 1 + y - yi;
            size_t sx = x + xi;
            if(sprite.data[yi * sprite.width + xi] &&
               sy < buffer->height && sx < buffer->width) 
            {
                buffer->data[sy * buffer->width + sx] = color;
            }
        }
    }
}

inline void create_alien_sprite(Sprite& sprite)
{
    // Make sprite
    sprite.width = 11;
    sprite.height = 8;
    sprite.data = new uint8_t[11 * 8]
    {
        0,0,1,0,0,0,0,0,1,0,0, // ..@.....@..
        0,0,0,1,0,0,0,1,0,0,0, // ...@...@...
        0,0,1,1,1,1,1,1,1,0,0, // ..@@@@@@@..
        0,1,1,0,1,1,1,0,1,1,0, // .@@.@@@.@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,0,1,1,1,1,1,1,1,0,1, // @.@@@@@@@.@
        1,0,1,0,0,0,0,0,1,0,1, // @.@.....@.@
        0,0,0,1,1,0,1,1,0,0,0  // ...@@.@@...
    };
}



inline void create_player_sprite(Sprite& sprite) {

    sprite.width = 11;
    sprite.height = 7;
    sprite.data = new uint8_t [11 * 7] 
    {
        0,0,0,0,0,1,0,0,0,0,0, // .....@.....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,0,0,0,1,1,1,0,0,0,0, // ....@@@....
        0,1,1,1,1,1,1,1,1,1,0, // .@@@@@@@@@.
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
        1,1,1,1,1,1,1,1,1,1,1, // @@@@@@@@@@@
    };

}