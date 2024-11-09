#include "TransformationScale.h"

void TransformationScale::scale(float factor) {
    _scaleFactor = factor;
    _scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(_scaleFactor));
    markDirty();
}

float TransformationScale::getScaleFactor() const {
    return _scaleFactor;
}

const glm::mat4& TransformationScale::getScaleMatrix() const {
    return _scaleMatrix;
}