#pragma once
#include "Transformation.h"

class TransformationTranslate : public Transformation {
private:
    glm::vec3 translation;
public:
    TransformationTranslate(glm::vec3 translation) : translation(translation) {}

    void setTranslation(glm::vec3 newTranslation) {
        translation = newTranslation;
    }

    glm::mat4 getMatrix() override {
        return glm::translate(glm::mat4(1.0f), translation);
    }
};