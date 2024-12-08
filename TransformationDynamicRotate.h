#pragma once
#include "Transformation.h"

class TransformationDynamicRotate : public Transformation, public IAnimationObject {
protected:
    glm::mat4 _matrix;
    glm::vec3 _axis;
    float _angleIncrement;

public:
    TransformationDynamicRotate(glm::mat4 initialMatrix, glm::vec3 axis, float increment)
        : _matrix(initialMatrix), _axis(axis), _angleIncrement(increment) {
    }

    void setAngleIncrement(float angleIncrement) {
        _angleIncrement = angleIncrement;
    }

    float getAngleIncrement() const {
        return _angleIncrement;
    }

    void setAxis(const glm::vec3& axis) {
        _axis = axis;
    }

    glm::vec3 getAxis() const {
        return _axis;
    }

    void update(float deltaTime) override {
        internalUpdate(deltaTime);
    }

    virtual void internalUpdate(float deltaTime) {
        float deltaAngle = _angleIncrement * deltaTime;
        _matrix = glm::rotate(_matrix, glm::radians(deltaAngle), _axis);
    }


    glm::mat4 getMatrix() override {
        return _matrix;
    }
};
