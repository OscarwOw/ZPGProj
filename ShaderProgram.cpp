#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


ShaderProgram::ShaderProgram() {
    programID = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(programID);
}

enum class ShaderType {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
};


unsigned int ShaderProgram::attachShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);

    glLinkProgram(programID);

    ShaderProgram::updateViewMatrix(glm::mat4(1.0f));
    ShaderProgram::updatePerspectiveMatrix(glm::perspective(glm::radians(45.0f), (float)(1500 / 1200), 0.1f, 100.0f));

    int isLinked;
    glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
    if (!isLinked) {
        GLint maxLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::string infoLog(maxLength, ' ');
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programID;
}

unsigned int ShaderProgram::compileShader(const std::string& shaderSource, unsigned int shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    const char* src = shaderSource.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    int isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        int maxLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        std::string message(maxLength, ' ');
        glGetShaderInfoLog(shader, maxLength, &maxLength, &message[0]);
        std::cerr << "Shader compilation failed: " << message << std::endl;
        glDeleteShader(shader);  // Don't leak the shader
        return 0;
    }

    return shader;
}

ShaderProgramSourceStrings ShaderProgram::parseShaders(const std::string& file) {
    std::ifstream stream(file);

    if (!stream.is_open()) {
        std::cerr << "Error: Could not open shader file: " << file << std::endl;
        return { "", "" };  // Return empty sources if the file can't be opened
    }

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}

std::string ShaderProgram::parseShader(const std::string& file)
{
    std::ifstream stream(file);
    std::string line, vertexString;
    
    while (getline(stream, line)) {       
        vertexString.append(line).append("\n");
    }
    return vertexString;
}

void ShaderProgram::setUniformMat4(const std::string& name, const glm::mat4& matrix) {
    GLuint location = glGetUniformLocation(programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::updateViewMatrix(const glm::mat4& viewMatrix)
{

    _viewMatrix = viewMatrix;
    //setUniformMat4("u_ViewMatrix", _viewMatrix);
}

void ShaderProgram::updatePerspectiveMatrix(const glm::mat4& viewMatrix)
{
    _perspectiveMatrix = viewMatrix;
    //setUniformMat4("u_Perspective", viewMatrix);
}

glm::mat4 ShaderProgram::getPerspectiveMatrix()
{
    return _perspectiveMatrix;
}

glm::mat4 ShaderProgram::getViewMatrix()
{
    return _viewMatrix;
}

//void ShaderProgram::updatePerspectiveMatrix() {
//    
//    glm::mat4 proj = glm::mat4(1.0f);
//    glm::mat4 view = glm::mat4(1.0f);
//    
//    view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
//    proj = glm::perspective(glm::radians(_perspective), (float)(1500/1200), 0.1f, 100.0f);
//
//
//    
//    setUniformMat4("u_Perspective", _perspective);
//    //updateViewMatrix(view);
//}

void ShaderProgram::use() {
    glUseProgram(programID);
}

GLuint ShaderProgram::getProgramID() const {
    return programID;
}
