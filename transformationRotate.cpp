#include "TransformationRotate.h"

void TransformationRotate::rotate(float rotationAngle, const glm::vec3& rotationAxis) {
    _angle = rotationAngle;
    _axis = rotationAxis;
    _rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_angle), _axis);
    markDirty();
}

void TransformationRotate::rotate(glm::mat4 rotationMatrix, float rotationAngle, const glm::vec3& rotationAxis ) {
    _angle = rotationAngle;
    _axis = rotationAxis;
    _rotationMatrix = glm::rotate(rotationMatrix, glm::radians(_angle), _axis);
    markDirty();
}



const glm::vec3& TransformationRotate::getAxis() const {
    return _axis;
}

float TransformationRotate::getAngle() const {
    return _angle;
}

const glm::mat4& TransformationRotate::getRotationMatrix() const {
    return _rotationMatrix;
}