#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformationComponent.h"

class TransformationTranslate : TransformationComponent {
public:
    TransformationTranslate() : _translation(0.0f) {}
    void translate(const glm::vec3& translationVector);
    void translate(glm::mat4 matrix, const glm::vec3& translationVector);
    const glm::vec3& getTranslation() const;
    const glm::mat4& getTranslationMatrix() const;

private:
    glm::vec3 _translation;
    glm::mat4 _translationMatrix = glm::mat4(1.0f);
};