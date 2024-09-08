#include "Shader.hpp"

Shader::Shader()
{


}

Shader::Shader(std::vector<uint*>&& shaderPrograms_) 
    : shaderPrograms(shaderPrograms_)
{
    
}

Shader::~Shader()
{


}

void Shader::assignShaderProgram(uint* shaderProgramId)
{
    shaderPrograms.push_back(shaderProgramId);
}

void Shader::unassignShaderProgram(uint* shaderProgramId)
{
    for (int i = 0; i < shaderPrograms.size(); i++) {
        if (shaderPrograms[i] == shaderProgramId) {
            uint* temp = shaderPrograms[shaderPrograms.size() - 1];
            shaderPrograms[shaderPrograms.size() - 1] = shaderPrograms[i];
            shaderPrograms[i] = temp;
            shaderPrograms.pop_back();
            break;
        }
    }
}

// void Shader::useShaderProgram(uint* shaderProgramId)
// {
//     for (int i = 0; i < shaderPrograms.size(); i++) {
//         if (shaderPrograms[i] == shaderProgramId) {
//             currentShaderProgramId = shaderPrograms[i];
//             glUseProgram(*currentShaderProgramId);
//             break;
//         }
//     }
// }

