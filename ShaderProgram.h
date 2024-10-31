#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

struct ShaderProgramSourceStrings
{
    std::string VertexSource;
    std::string FragmentSource;
};


class ShaderProgram : public ICameraObserver {
public:
    ShaderProgram();
    ShaderProgram(GLuint programID);
    ~ShaderProgram();

    // Method to load, compile and link shaders
    unsigned int attachShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    void use();
    ShaderProgramSourceStrings parseShaders(const std::string& file);
    std::string parseShader(const std::string& file);
    GLuint getProgramID() const;
    
    void setUniformMat4(const std::string& name, const glm::mat4& matrix);
    void setViewMatrix(const glm::mat4& viewMatrix) override;
    void setPerspectiveMatrix(const glm::mat4& viewMatrix) override;

    glm::mat4 getPerspectiveMatrix();
    glm::mat4 getViewMatrix();

private:
    GLuint _programID;

    float _perspective = 45.0f;
    glm::mat4 _viewMatrix;
    glm::mat4 _perspectiveMatrix;

    // Helper functions to compile individual shaders
    GLuint compileShader(const std::string& shaderSource, GLenum shaderType);
};

#endif
