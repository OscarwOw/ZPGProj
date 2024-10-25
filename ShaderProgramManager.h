#pragma once
#include <map>
#include <string>
#include "ShaderProgram.h"

class ShaderProgramManager {
public:

    static ShaderProgramManager& getInstance();

    void loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    void loadShader(const std::string& name, const std::string& shaderPath);

    ShaderProgram* getShader(const std::string& name);

    void useShader(const std::string& name);
    ShaderProgram* activeShader;

private:
    ShaderProgramManager() {}
    ShaderProgramManager(const ShaderProgramManager&) = delete;
    ShaderProgramManager& operator=(const ShaderProgramManager&) = delete;

    std::map<std::string, ShaderProgram*> shaders; 
};
