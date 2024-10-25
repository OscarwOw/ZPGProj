#include "ShaderProgramManager.h"

ShaderProgramManager& ShaderProgramManager::getInstance() {
    static ShaderProgramManager instance;
    return instance;
}

void ShaderProgramManager::loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgramSourceStrings source = {
         shaderProgram->parseShader(vertexPath),
         shaderProgram->parseShader(fragmentPath)
    };
    unsigned int shader = shaderProgram->attachShader(source.VertexSource, source.FragmentSource);
    shaders[name] = shaderProgram;
}

void ShaderProgramManager::loadShader(const std::string& name, const std::string& shaderPath)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgramSourceStrings source = shaderProgram->parseShaders(shaderPath);
    unsigned int shader = shaderProgram->attachShader(source.VertexSource, source.FragmentSource);
    shaders[name] = shaderProgram;
}

ShaderProgram* ShaderProgramManager::getShader(const std::string& name)
{
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    }
    return nullptr;
}

void ShaderProgramManager::useShader(const std::string& name) {
    ShaderProgram* shader = getShader(name);
    if (shader && shader != activeShader) {
        shader->use();
        activeShader = shader;
    }
}
