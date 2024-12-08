#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <glm/ext/matrix_transform.hpp>
#include "RandomMovementCube.h"
#include "IAnimationObject.h"
#include <glm/gtc/random.hpp>
#include "DynamicTranslateCubeData.h"


//TODO clean up and put to separate files with .cpp and .h
class Transformation {
public:
    virtual ~Transformation() = default;
    virtual glm::mat4 getMatrix() = 0; 
};


class NewTransformationTranslate : public Transformation {
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


class NewTransformationRotate : public Transformation {
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

class NewTransformationScale : public Transformation {
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

class NewTransformationDynamicTranslate : public Transformation, public IAnimationObject {
protected:
    glm::mat4 _matrix;
    glm::vec3 _increment;  

public:
    NewTransformationDynamicTranslate( glm::mat4& initialMatrix)
        : _matrix(initialMatrix), _increment(glm::vec3(0.0f)) {
    }

    void setIncrement( glm::vec3& increment) {
        _increment = increment;
    }

    glm::vec3 getIncrement() {
        return _increment;
    }

    void update(float deltaTime) override {
        internalUpdate(deltaTime);
    }

    virtual void internalUpdate(float deltaTime) {
        glm::vec3 deltaTranslate = _increment *  deltaTime; 
        _matrix = glm::translate(_matrix, deltaTranslate);
    }

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

        initialize();
    }

    NewTransformationDynamicTranslateCube(DynamicTranslateCubeData data) //lenost dela divy
        : NewTransformationDynamicTranslate(data.initialMatrix),
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
        NewTransformationDynamicTranslate::internalUpdate(deltaTime);
        check();
    }
};

class NewTransformationDynamicRotate : public Transformation, public IAnimationObject {
protected:
    glm::mat4 _matrix;
    glm::vec3 _axis;         
    float _angleIncrement;   

public:
    NewTransformationDynamicRotate(glm::mat4 initialMatrix, glm::vec3 axis, float increment)
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



class NewTransformationBezier : public Transformation, public IAnimationObject {
private:
    glm::mat4 _matrix;
    std::vector<glm::vec3> _controlPoints;
    float t;       
    float speed;     

public:
    NewTransformationBezier(
        const glm::mat4& initialMatrix,
        const std::vector<glm::vec3>& points,
        float speed = 0.5f
    )
        : _matrix(initialMatrix), _controlPoints(points), t(0.0f), speed(speed)
    {
    }

    void update(float deltaTime) override {
        t += speed * deltaTime;

        while (t > 1.0f) {
            t -= 1.0f;
        }   

        internalUpdate();
    }

    glm::mat4 getMatrix() override {
        return _matrix;
    }

private:
    void internalUpdate() {
        glm::vec3 position = generalBezierPoint(t);
        _matrix = glm::translate(glm::mat4(1.0f), position);
    }

    unsigned int binomialCoefficient(unsigned int n, unsigned int k) {
        if (k > n) return 0;
        if (k == 0 || k == n) return 1;
        unsigned int result = 1;
        for (unsigned int i = 1; i <= k; ++i) {
            result = result * (n - (k - i)) / i;
        }
        return result;
    }

    glm::vec3 generalBezierPoint(float t) {
        glm::vec3 result(0.0f);
        size_t n = _controlPoints.size();
        if (n == 0) return result;

        for (size_t i = 0; i < n; ++i) {
            unsigned int c = binomialCoefficient(static_cast<unsigned int>(n - 1), static_cast<unsigned int>(i));
            float blend = c * std::pow(1.0f - t, (float)(n - 1 - i)) * std::pow(t, (float)i);
            result += blend * _controlPoints[i];
        }

        return result;
    }
};


