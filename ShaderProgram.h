#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#pragma once

#include <GL/glew.h>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "ShaderKind.h"
#include "ShaderProgramSourceStrings.h"
#include "ILightObserver.h"
#include "MaterialProperties.h"
#include "LightData.h"


class ShaderProgram : public ICameraObserver, public ILightObserver {
public:
    ShaderProgram();
    ShaderProgram(GLuint programID);
    ~ShaderProgram();

    // Method to load, compile and link shaders
    unsigned int attachShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    void use();
    void use(int id);
    ShaderProgramSourceStrings parseShaders(const std::string& file);
    std::string parseShader(const std::string& file);
    GLuint getProgramID() const;
    
    void setUniformMat4(const std::string& name, const glm::mat4& matrix);
    void setUniformVec3(const std::string& name, const glm::vec3& vector);

    void setUniformFloat(const std::string& name, const float& vector);

    void setUniformInt(const std::string& name, int value);

    void updateMaterialProperties(const MaterialProperties& material);


#pragma region ICameraObserver overrides
    void setViewMatrix(const glm::mat4& viewMatrix) override;
    void setPerspectiveMatrix(const glm::mat4& viewMatrix) override;
    void setCameraPosition(const glm::vec3& cameraPosition) override;

    glm::mat4 getPerspectiveMatrix();
    glm::mat4 getViewMatrix();
    glm::vec3 getCameraPosition();
#pragma endregion

#pragma region ILightObserver overides
    void setLightsVector(std::vector<LightData> data) override;
#pragma endregion

    void addLightSource(const glm::vec4& color, float intensity, const glm::vec3& position);
    void updateLightSources();

private:
    GLuint _programID;

    float _perspective = 45.0f;
    glm::mat4 _viewMatrix;
    glm::mat4 _perspectiveMatrix;
    glm::vec3 _cameraPosition;

    glm::vec4 _lightColor;
    float _lightIntensity;
    glm::vec3 _lightPosition;

    std::vector<LightData> _lightData;

    bool _hasLightColor, _hasLightIntensity, _hasLightPosition = false;

    // Helper functions to compile individual shaders
    GLuint compileShader(const std::string& shaderSource, GLenum shaderKind);
};

#endif
