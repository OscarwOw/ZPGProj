#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "NewTransformation.h"

class TransformationComposite : public Transformation {
private:
    std::vector<std::shared_ptr<Transformation>> transformations;

    //bool isDirty = true;
    glm::mat4 cachedMatrix = glm::mat4(1.0f);

public:
    void addTransformation(Transformation* transformation) {
        std::shared_ptr<Transformation> transformationShared(transformation);
        transformations.push_back(transformationShared);
        //isDirty = true;
    }

    void removeTransformation(int index) {
        if (index >= 0 && index < transformations.size()) {
            transformations.erase(transformations.begin() + index);
            //isDirty = true;
        }
    }

    void updateTransformation(int index, Transformation* newTransformation) {
        if (index >= 0 && index < transformations.size()) {
            transformations[index] = std::shared_ptr<Transformation>(newTransformation);
            //isDirty = true;
        }
    }

    glm::mat4 getMatrix() override {
        //if (isDirty) {
            cachedMatrix = glm::mat4(1.0f);
            for (auto& transformation : transformations) {
                cachedMatrix *= transformation->getMatrix();
            }
            //isDirty = false;
        //}
        return cachedMatrix;
    }

    void markDirty() {
        //isDirty = true;
    }

    Transformation* getTransformation(int index) {
        if (index >= 0 && index < transformations.size()) {
            return transformations[index].get();
        }
        return nullptr;
    }
};
