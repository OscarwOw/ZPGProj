// Transformation.h
#pragma once
#include "TransformationDynamicRotate.h"
#include "TransformationDynamicTranslate.h"

class Transformation : 
    public TransformationDynamicRotate, public TransformationDynamicTranslate {
private: 
    glm::mat4 _modelMatrix;
    bool _isTransformationDirty = true;

    void updateModelMatrix() {
        //_modelMatrix = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix(); //TODO to vector with first part for default positions
        _isTransformationDirty = false; 
    }

public:
    Transformation() = default;



    void updateTransformations(float deltaTime) {

        float angle = getDynamicAngleIncrement(deltaTime);
        if (angle != 0) {
            //rotate(getRotationMatrix(), angle, getDynamicAxis());
        }
        glm::vec3 translateVector = getDynamicTranslate();
        if (translateVector != glm::vec3(0.0f)) {
            //translate(getTranslationMatrix(), getDynamicTranslateIncrement(deltaTime));
        }
    }

    glm::mat4 getModelMatrix() {
        if (_isTransformationDirty) {
            updateModelMatrix();
        }
        return _modelMatrix;
    }
};
