#include "TransformationTranslate.h"

void TransformationTranslate::translate(const glm::vec3& translationVector) {
    _translation = translationVector;
    _translationMatrix = glm::translate(glm::mat4(1.0f), _translation);
    markDirty();
}

void TransformationTranslate::translate(glm::mat4 matrix, const glm::vec3& translationVector)
{
    _translation += translationVector;
    _translationMatrix = glm::translate(matrix, translationVector);
    markDirty();
}

const glm::vec3& TransformationTranslate::getTranslation() const {
    return _translation;
}

const glm::mat4& TransformationTranslate::getTranslationMatrix() const {
    return _translationMatrix;
}
