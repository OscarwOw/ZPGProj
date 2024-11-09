#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class TransformationRotate : public TransformationComponent {
public:
    TransformationRotate() : _angle(0.0f), _axis(0.0f, 1.0f, 0.0f) {}

    void rotate(float rotationAngle, const glm::vec3& rotationAxis);

    void rotate(glm::mat4 rotationMatrix, float rotationAngle, const glm::vec3& rotationAxis);

    const glm::vec3& getAxis() const;

    float getAngle() const;

    const glm::mat4& getRotationMatrix() const;

private:
    float _angle;
    glm::vec3 _axis;
    glm::mat4 _rotationMatrix = glm::mat4(1.0f);
};