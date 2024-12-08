#pragma once
#include "Transformation.h"

class TransformationScale : public Transformation {
private:
    glm::vec3 scale;
public:
    TransformationScale(glm::vec3 scale) : scale(scale) {}

    void setScale(glm::vec3 newScale) {
        scale = newScale;
    }

    glm::mat4 getMatrix() override {
        return glm::scale(glm::mat4(1.0f), scale);
    }
};