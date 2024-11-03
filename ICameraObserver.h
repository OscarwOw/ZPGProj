#pragma once
#include <glm/ext/matrix_float4x4.hpp>
class ICameraObserver {
public:
    virtual void setViewMatrix(const glm::mat4& viewMatrix) = 0;
    virtual void setPerspectiveMatrix(const glm::mat4& viewMatrix) = 0;
    virtual void setCameraPosition(const glm::vec3& cameraPosition) = 0;
};