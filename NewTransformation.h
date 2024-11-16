#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <glm/ext/matrix_transform.hpp>
#include "RandomMovementCube.h"
#include "IAnimationObject.h"
#include <glm/gtc/random.hpp>

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

class NewTransformationDynamicTranslate : public NewTransformation, public IAnimationObject {
protected:
    glm::mat4 _matrix;
    glm::vec3 _increment;  // Increment speed (units per second)

public:
    // Constructor initializing with a given matrix
    NewTransformationDynamicTranslate( glm::mat4& initialMatrix)
        : _matrix(initialMatrix), _increment(glm::vec3(0.0f)) {
    }

    // Set increment vector
    void setIncrement( glm::vec3& increment) {
        _increment = increment;
    }

    // Get increment vector
    glm::vec3 getIncrement() {
        return _increment;
    }

    // Update transformation based on deltaTime
    void update(float deltaTime) override {
        internalUpdate(deltaTime);
    }

    virtual void internalUpdate(float deltaTime) {
        glm::vec3 deltaTranslate = _increment *  deltaTime;  // Convert ms to seconds
        _matrix = glm::translate(_matrix, deltaTranslate);
    }

    // Get current transformation matrix
    glm::mat4 getMatrix() override {
        return _matrix;
    }
};



class NewTransformationDynamicTranslateCube : public NewTransformationDynamicTranslate {
public:
    NewTransformationDynamicTranslateCube(float speed, float cubeSize, glm::mat4& initialMatrix,
        float maxHeight, float maxWidth, float maxLength,
        float minHeight, float minWidth, float minLength)
        : NewTransformationDynamicTranslate(initialMatrix),
        _speed(speed), _cubeSize(cubeSize),
        _maxHeight(maxHeight), _maxWidth(maxWidth), _maxLength(maxLength),
        _minHeight(minHeight), _minWidth(minWidth), _minLength(minLength) {
    
        float heightDistance = maxHeight - minHeight;
        float widthDistance = maxWidth - minWidth;
        float lengthDistance = maxLength - minLength;

        float minDistance = std::min({ heightDistance, widthDistance, lengthDistance });

        if (cubeSize > minDistance / 2.0f) {
            cubeSize = minDistance / 2.0f;
        }
        _randomMovementData.cubeSize = cubeSize;
        _randomMovementData.center = initialMatrix[3];
        generateCube();
        generateMovement();
    }

private:
    float _speed;
    float _cubeSize;
    float _maxHeight;
    float _maxWidth;
    float _maxLength;
    float _minHeight;
    float _minWidth;
    float _minLength;
    RandomMovementCube _randomMovementData;


    void generateCube() {
        glm::vec3 objectPosition = glm::vec3(_matrix[3]);

        glm::vec3 initialCenter = objectPosition;

        if (initialCenter.x + _cubeSize > _maxWidth) {
            initialCenter.x = _maxWidth - _cubeSize;
        }
        if (initialCenter.x - _cubeSize < _minWidth) {
            initialCenter.x = _minWidth + _cubeSize;
        }

        if (initialCenter.y + _cubeSize > _maxHeight) {
            initialCenter.y = _maxHeight - _cubeSize;
        }
        if (initialCenter.y - _cubeSize < _minHeight) {
            initialCenter.y = _minHeight + _cubeSize;
        }

        if (initialCenter.z + _cubeSize > _maxLength) {
            initialCenter.z = _maxLength - _cubeSize;
        }
        if (initialCenter.z - _cubeSize < _minLength) {
            initialCenter.z = _minLength + _cubeSize;
        }

        _randomMovementData.center = initialCenter;
    }

    void generateMovement() {
        glm::vec3 movementDirection = glm::sphericalRand(1.0f);
        movementDirection = glm::normalize(movementDirection) * _speed;

        glm::vec3 nextPosition = glm::vec3(_matrix[3]) + (movementDirection * (1.0f / 50.0f));

        if (nextPosition.x + _randomMovementData.cubeSize > _maxWidth || nextPosition.x - _randomMovementData.cubeSize < _minWidth) {
            movementDirection.x = -movementDirection.x;
        }
        if (nextPosition.y + _randomMovementData.cubeSize > _maxHeight || nextPosition.y - _randomMovementData.cubeSize < _minHeight) {
            movementDirection.y = -movementDirection.y;
        }
        if (nextPosition.z + _randomMovementData.cubeSize > _maxLength || nextPosition.z - _randomMovementData.cubeSize < _minLength) {
            movementDirection.z = -movementDirection.z;
        }
        setIncrement(movementDirection);
    }

    void check() {
        glm::vec3 currentPosition = glm::vec3(_matrix[3]);

        bool isWithinBounds = (currentPosition.x + _randomMovementData.cubeSize <= _maxWidth &&
            currentPosition.x - _randomMovementData.cubeSize >= _minWidth &&
            currentPosition.y + _randomMovementData.cubeSize <= _maxHeight &&
            currentPosition.y - _randomMovementData.cubeSize >= _minHeight &&
            currentPosition.z + _randomMovementData.cubeSize <= _maxLength &&
            currentPosition.z - _randomMovementData.cubeSize >= _minLength);

        if (!isWithinBounds) {
            generateCube();
            generateMovement();
        }
    }
    void update(float deltaTime) override {
        internalUpdate(deltaTime);
    }

    void internalUpdate(float deltaTime) override {
        NewTransformationDynamicTranslate::internalUpdate(deltaTime);
        check();
    }
};


