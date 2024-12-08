#pragma once
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "ShaderLoader.h"

class ShaderProgramManager {
public:
    static ShaderProgramManager& getInstance();

    std::string CreateShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& name);
    std::string CreateShader(const std::string& shaderPath, const std::string& name);
    std::string CreateShaderNemec(const char* vertexFile, const char* fragmentFile, std::string name);

    ShaderProgram* getShader(const std::string& name);

    void useShader(const std::string& name);
    
private:
    ShaderProgramManager() {}
    ShaderProgramManager(const ShaderProgramManager&) = delete;
    ShaderProgramManager& operator=(const ShaderProgramManager&) = delete;

    static ShaderLoader* _shaderLoader;

    std::map<std::string, ShaderProgram*> _shaders;
    std::map<std::string, unsigned int> _namesIndexHolder;

    std::string CreateShader(ShaderProgramSourceStrings source, ShaderProgram* shaderProgram, const std::string& name);
    std::string CreateShaderID(std::string shaderType);
    ShaderProgram* _activeShader;
};
