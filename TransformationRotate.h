#pragma once
#include "Transformation.h"

class TransformationRotate : public Transformation {
private:
    glm::vec3 axis;
    float angle;
public:
    TransformationRotate(float angle, glm::vec3 axis) : angle(angle), axis(axis) {}

    void setRotation(float newAngle, glm::vec3 newAxis) {
        angle = newAngle;
        axis = newAxis;
    }

    glm::mat4 getMatrix() override {
        return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    }
};