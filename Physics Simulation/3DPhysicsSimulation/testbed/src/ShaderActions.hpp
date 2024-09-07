// Header only. Lists actions that can be done on (/with?) shaders 
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.hpp"

#define RESOURCE_PATH "../testbed/assets/"



namespace shader {
    // *******************************
    //      METHOD DECLARATIONS 
    // *******************************

    inline std::string loadShaderSrc(const std::string& filename);
    inline GLuint compileShader(const std::string& filePath, GLenum type);

    // Links the vertex and fragement shader to the given shader program. 
    // Also deletes the vertex and fragemnt shaders. 
    inline void linkShaderProgram(uint& shaderProgram, uint& vertexShader, uint& fragmentShader);

    inline void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
    inline void useAndDraw(uint, GLenum mode, GLsizei count, GLenum type, const void *indices);
    inline void useShader(uint shaderProgram);
    inline void setMat4(uint shaderProgram, const char* name, glm::mat4 val);
    inline void setBool(uint shaderProgram, const char* name, bool value);
    inline void setInt(uint shaderProgram, const char* name, int value);
    inline void setFloat(uint shaderProgram, const char* name, float value);
    inline void set4Float(uint shaderProgram, const char* name, float v1, float v2, float v3, float v4);

    // *******************************
    //      METHOD DEFINITIONS 
    // *******************************


    std::string loadShaderSrc(const std::string& filename)
    {
        std::ifstream file;
        std::stringstream buf;

        std::string ret = "";

        file.open(filename);

        if (!file.is_open()) {
            std::cerr<<"File "<<filename<<" is not open!"<<std::endl;
            exit(1);
        }

        buf << file.rdbuf();
        ret = buf.str();

        file.close(); 
        return ret;
    }

    GLuint compileShader(const std::string& filePath, GLenum type)
    {

        int success;
        char infoLog[512];

        GLuint ret  = glCreateShader(type);
        std::string shaderSrc = loadShaderSrc(filePath);
        const GLchar* shader = shaderSrc.c_str();
        glShaderSource(ret, 1, &shader, NULL);
        glCompileShader(ret);

        glGetShaderiv(ret, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(ret, 512, NULL, infoLog);
            std::cout<<"Error in shader compilation: "<<std::endl<<infoLog<<std::endl;
            exit(1);
        }
        
        return ret;
    }

    void linkShaderProgram(uint& shaderProgram, uint& vertexShader, uint& fragmentShader)
    {


        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // catch error
        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cout<< "Linking Error:" <<std::endl<<infoLog<<std::endl;
            exit(1);
        }

        // can delete vertex and frag shader now
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }

    void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)
    {    
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void useAndDraw(uint shaderProgram, GLenum mode, GLsizei count, GLenum type, const void *indices)
    {
        useShader(shaderProgram);
        glDrawElements(mode, count, type, indices);
    }

    void useShader(uint shaderProgram) 
    {
        GLint current = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &current);
        if (shaderProgram == current) return;

        glUseProgram(shaderProgram);
    }

    void setMat4(uint shaderProgram, const char* name, glm::mat4 val)
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, glm::value_ptr(val));
    }

    void setBool(uint shaderProgram, const char* name, bool value)
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name), (int)value);
    }

    void setInt(uint shaderProgram, const char* name, int value)
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name), value);    
    }

    void setFloat(uint shaderProgram, const char* name, float value)
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name), value);    
    }

    void set4Float(uint shaderProgram, const char* name, float v1, float v2, float v3, float v4)
    {
        glUniform4f(glGetUniformLocation(shaderProgram, name), v1, v2, v3, v4);
    }


}