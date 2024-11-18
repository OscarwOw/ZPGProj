#pragma once
#include "DrawableObject.h"
#include "RandomMovementCube.h"
#include <glm/gtc/random.hpp>

class AnimationObject {
public:
    AnimationObject(float speed, float cubeSize, DrawableObject* object,
        float maxHeight, float maxWidth, float maxLength,
        float minHeight, float minWidth, float minLength) {

        // Calculate the distances for each dimension
        float heightDistance = maxHeight - minHeight;
        float widthDistance = maxWidth - minWidth;
        float lengthDistance = maxLength - minLength;

        // Find the smallest distance among height, width, and length
        float minDistance = std::min({ heightDistance, widthDistance, lengthDistance });

        // Ensure cubeSize is at least 2 times smaller than the smallest distance
        if (cubeSize > minDistance / 2.0f) {
            cubeSize = minDistance / 2.0f;
        }

        // Initialize member variables
        _speed = speed;
        _cubeSize = cubeSize;
        _object = object;
        _maxHeight = maxHeight;
        _maxWidth = maxWidth;
        _maxLength = maxLength;
        _minHeight = minHeight;
        _minWidth = minWidth;
        _minLength = minLength;

        // Generate the cube with adjusted parameters
        generateCube();
        generateMovement();
    }

    void generateCube() {
        glm::vec3 objectPosition = _object->getPosition();

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

        glm::vec3 nextPosition = _object->getPosition() + (movementDirection * (1.0f / 50.0f));

        if (nextPosition.x + _randomMovementData.cubeSize > _maxWidth || nextPosition.x - _randomMovementData.cubeSize < _minWidth) {
            movementDirection.x = -movementDirection.x; 
        }
        if (nextPosition.y + _randomMovementData.cubeSize > _maxHeight || nextPosition.y - _randomMovementData.cubeSize < _minHeight) {
            movementDirection.y = -movementDirection.y; 
        }
        if (nextPosition.z + _randomMovementData.cubeSize > _maxLength || nextPosition.z - _randomMovementData.cubeSize < _minLength) {
            movementDirection.z = -movementDirection.z; 
        }

        //TODO dyn trans
        //_object->transformation.setDynamicTranslate(movementDirection);
    }

    void check() {
        glm::vec3 currentPosition = _object->getPosition();

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

private:
	DrawableObject* _object;
	RandomMovementCube _randomMovementData;
	float _speed;
	float _cubeSize;
	float _maxHeight;
	float _maxWidth;
	float _maxLength;
	float _minHeight;
	float _minWidth;
	float _minLength;
};