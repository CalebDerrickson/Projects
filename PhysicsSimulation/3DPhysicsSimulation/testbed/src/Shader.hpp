#pragma once


#include <string>
#include <vector>

#include "utils.hpp"
class Shader{
public:
    Shader();
    Shader(std::vector<uint*> && shaderPrograms_);
    ~Shader();

    void assignShaderProgram(uint* shaderProgramId);
    void unassignShaderProgram(uint* shaderProgramId);
    // void useShaderProgram(uint* shaderProgramId);

    std::vector<uint*> shaderPrograms;
    uint* currentShaderProgramId;
};