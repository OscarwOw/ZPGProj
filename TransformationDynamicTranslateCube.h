#pragma once
#include "TransformationDynamicTranslate.h"

class TransformationDynamicTranslateCube : public TransformationDynamicTranslate {
public:
    TransformationDynamicTranslateCube(float speed, float cubeSize, glm::mat4& initialMatrix,
        float maxHeight, float maxWidth, float maxLength,
        float minHeight, float minWidth, float minLength)
        : TransformationDynamicTranslate(initialMatrix),
        _speed(speed), _cubeSize(cubeSize),
        _maxHeight(maxHeight), _maxWidth(maxWidth), _maxLength(maxLength),
        _minHeight(minHeight), _minWidth(minWidth), _minLength(minLength) {

        initialize();
    }

    TransformationDynamicTranslateCube(DynamicTranslateCubeData data) //lenost dela divy
        : TransformationDynamicTranslate(data.initialMatrix),
        _speed(data.speed), _cubeSize(data.cubeSize),
        _maxHeight(data.maxHeight), _maxWidth(data.maxWidth), _maxLength(data.maxLength),
        _minHeight(data.minHeight), _minWidth(data.minWidth), _minLength(data.minLength) {

        initialize();
    }

    void initialize() {
        float heightDistance = _maxHeight - _minHeight;
        float widthDistance = _maxWidth - _minWidth;
        float lengthDistance = _maxLength - _minLength;

        float minDistance = std::min({ heightDistance, widthDistance, lengthDistance });

        if (_cubeSize > minDistance / 2.0f) {
            _cubeSize = minDistance / 2.0f;
        }

        _randomMovementData.cubeSize = _cubeSize;
        _randomMovementData.center = _matrix[3];
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
        TransformationDynamicTranslate::internalUpdate(deltaTime);
        check();
    }
};