#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <glm/ext/matrix_transform.hpp>

class NewTransformation {
public:
    virtual ~NewTransformation() = default;
    virtual glm::mat4 getMatrix() = 0; 
};


class NewTransformationTranslate : public NewTransformation {
private:
    glm::vec3 translation;
public:
    NewTransformationTranslate(glm::vec3 translation) : translation(translation) {}

    void setTranslation(glm::vec3 newTranslation) {
        translation = newTranslation;
    }

    glm::mat4 getMatrix() override {
        return glm::translate(glm::mat4(1.0f), translation);
    }
};


class NewTransformationRotate : public NewTransformation {
private:
    glm::vec3 axis;
    float angle; 
public:
    NewTransformationRotate(float angle, glm::vec3 axis) : angle(angle), axis(axis) {}

    void setRotation(float newAngle, glm::vec3 newAxis) {
        angle = newAngle;
        axis = newAxis;
    }

    glm::mat4 getMatrix() override {
        return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    }
};

class NewTransformationScale : public NewTransformation {
private:
    glm::vec3 scale;
public:
    NewTransformationScale(glm::vec3 scale) : scale(scale) {}

    void setScale(glm::vec3 newScale) {
        scale = newScale;
    }

    glm::mat4 getMatrix() override {
        return glm::scale(glm::mat4(1.0f), scale);
    }
};
