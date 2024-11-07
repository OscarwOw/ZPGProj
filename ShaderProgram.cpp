#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


ShaderProgram::ShaderProgram() {
    _programID = glCreateProgram();
}

ShaderProgram::ShaderProgram(unsigned int programID) {
    _programID = programID;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(_programID);
}


unsigned int ShaderProgram::attachShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    unsigned int vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    glAttachShader(_programID, vertexShader);
    glAttachShader(_programID, fragmentShader);

    glLinkProgram(_programID);

    ShaderProgram::setViewMatrix(glm::mat4(1.0f));
    ShaderProgram::setPerspectiveMatrix(glm::perspective(glm::radians(45.0f), (float)(1500 / 1200), 0.1f, 100.0f));

    int isLinked;
    glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
    if (!isLinked) {
        GLint maxLength;
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::string infoLog(maxLength, ' ');
        glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
        std::cerr << "Shader linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return _programID;
}

unsigned int ShaderProgram::compileShader(const std::string& shaderSource, unsigned int shaderKind) {
    unsigned int shader = glCreateShader(shaderKind);
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
    ShaderKind type = ShaderKind::NONE;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderKind::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderKind::FRAGMENT;
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
    GLuint location = glGetUniformLocation(_programID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniformVec3(const std::string& name, const glm::vec3& vector) {
    GLuint location = glGetUniformLocation(_programID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::setUniformFloat(const std::string& name, const float& value) {
    GLuint location = glGetUniformLocation(_programID, name.c_str());
    glUniform1f(location, value);
}

void ShaderProgram::setUniformInt(const std::string& name, int value) {
    GLuint location = glGetUniformLocation(_programID, name.c_str());
    glUniform1i(location, value);
}


void ShaderProgram::updateMaterialProperties(const MaterialProperties& material) {
    setUniformVec3("materialAmbient", material.ambientReflectivity);
    setUniformVec3("materialDiffuse", material.diffuseReflectivity);
    setUniformVec3("materialSpecular", material.specularReflectivity);
    setUniformFloat("materialShininess", material.shininess);
}

#pragma region ICameraObserver overrides
void ShaderProgram::setViewMatrix(const glm::mat4& viewMatrix)
{
    _viewMatrix = viewMatrix;
}

void ShaderProgram::setPerspectiveMatrix(const glm::mat4& perspectiveMatrix)
{
    _perspectiveMatrix = perspectiveMatrix;
}

void ShaderProgram::setCameraPosition(const glm::vec3& cameraPosition)
{
    //printf("camera position changed");
    _cameraPosition = cameraPosition;
}

glm::mat4 ShaderProgram::getPerspectiveMatrix()
{
    return _perspectiveMatrix;
}

glm::mat4 ShaderProgram::getViewMatrix()
{
    return _viewMatrix;
}

glm::vec3 ShaderProgram::getCameraPosition()
{
    return _cameraPosition;
}
#pragma endregion

#pragma region ILightObserver overrides

void ShaderProgram::setLightsVector(std::vector<LightData> data)
{
    _lightData = data;
}

void ShaderProgram::updateLightSources() {
    use(); // Make sure the shader program is active

    // Set the number of light sources as an integer
    setUniformInt("numLights", static_cast<int>(_lightData.size()));

    // Iterate over each light and set its properties in the shader
    for (size_t i = 0; i < _lightData.size(); ++i) {
        std::string indexStr = std::to_string(i);
        setUniformVec3("lightSources[" + indexStr + "].position", _lightData[i].position);
        setUniformVec3("lightSources[" + indexStr + "].color", glm::vec3(_lightData[i].color));
    }
}


#pragma endregion


void ShaderProgram::use() {
    glUseProgram(_programID);
}

GLuint ShaderProgram::getProgramID() const {
    return _programID;
}
