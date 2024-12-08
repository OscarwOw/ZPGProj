#pragma once
#include "Transformation.h"

class TransformationDynamicTranslate : public Transformation, public IAnimationObject {
protected:
    glm::mat4 _matrix;
    glm::vec3 _increment;

public:
    TransformationDynamicTranslate(glm::mat4& initialMatrix)
        : _matrix(initialMatrix), _increment(glm::vec3(0.0f)) {
    }

    void setIncrement(glm::vec3& increment) {
        _increment = increment;
    }

    glm::vec3 getIncrement() {
        return _increment;
    }

    void update(float deltaTime) override {
        internalUpdate(deltaTime);
    }

    virtual void internalUpdate(float deltaTime) {
        glm::vec3 deltaTranslate = _increment * deltaTime;
        _matrix = glm::translate(_matrix, deltaTranslate);
    }

    glm::mat4 getMatrix() override {
        return _matrix;
    }
};