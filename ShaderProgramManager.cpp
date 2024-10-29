#include "ShaderProgramManager.h"
#include <cstdlib>

ShaderProgramManager& ShaderProgramManager::getInstance() {
    static ShaderProgramManager instance;
    return instance;
}

//TODO Code Organization consistency
#pragma region Create Shader
std::string ShaderProgramManager::CreateShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgramSourceStrings source = {
         shaderProgram->parseShader(vertexPath),
         shaderProgram->parseShader(fragmentPath)
    };
    return CreateShader(source, shaderProgram, name);
}

std::string ShaderProgramManager::CreateShader(const std::string& name, const std::string& shaderPath)
{
    ShaderProgram* shaderProgram = new ShaderProgram();
    ShaderProgramSourceStrings source = shaderProgram->parseShaders(shaderPath);
    return CreateShader(source, shaderProgram, name);
}

std::string ShaderProgramManager::CreateShader(ShaderProgramSourceStrings source, ShaderProgram* shaderProgram, const std::string& name) {
    unsigned int shader = shaderProgram->attachShader(source.VertexSource, source.FragmentSource);
    std::string accessString = CreateShaderID(name);
    _shaders[accessString] = shaderProgram;
    return accessString;
}

std::string ShaderProgramManager::CreateShaderID(std::string shaderType)
{
    if (_namesIndexHolder.find(shaderType) == _namesIndexHolder.end()) {
        _namesIndexHolder[shaderType] = 0;
    }
    else {
        _namesIndexHolder[shaderType]++;
    }
    return shaderType + "_" + std::to_string(_namesIndexHolder[shaderType]);
}
#pragma endregion


ShaderProgram* ShaderProgramManager::getShader(const std::string& name)
{
    auto it = _shaders.find(name);
    if (it != _shaders.end()) {
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


