#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class TransformationDynamicRotate {
public:
    TransformationDynamicRotate() : _angle(0.0f), _axis(0.0f, 1.0f, 0.0f) {}

    void setDynamicAngle(float angle) { _angle = angle; }
    void setDynamicAxis(glm::vec3 axis) { _axis = axis; }
    float getDynamicAngleIncrement(float deltaTime) {
        return _angle * (deltaTime / 1000); //not corrent if we gradualy increase speed
    }
    float getDynamicAngle() {
        return _angle; //not corrent if we gradualy increase speed
    }
    glm::vec3 getDynamicAxis() {
        return _axis; //not corrent if we gradualy increase speed
    }
    


private:
    /* those are current rotation speed values */
    float _angle;
    glm::vec3 _axis;
};