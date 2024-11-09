#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class TransformationScale : public TransformationComponent {
public:
    TransformationScale() : _scaleFactor(1.0f) {}

    void scale(float factor);
    float getScaleFactor() const;
    const glm::mat4& getScaleMatrix() const;

private:
    float _scaleFactor;
    glm::mat4 _scaleMatrix = glm::mat4(1.0f);
};