#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class TransformationDynamicTranslate  {
public:
    TransformationDynamicTranslate() : _axisSpeed(0.0f, 0.0f, 0.0f) {}

    void setDynamicTranslate(glm::vec3 axisSpeed) { _axisSpeed = axisSpeed; }
    glm::vec3 getDynamicTranslate() { return _axisSpeed; }
    glm::vec3 getDynamicTranslateIncrement(float deltaTime) { return _axisSpeed * (deltaTime / 1000); }

private:
    /* those are current rotation speed values */
    glm::vec3 _axisSpeed;
};