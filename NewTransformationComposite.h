#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "NewTransformation.h"

class TransformationComposite : public NewTransformation {
private:
    std::vector<std::shared_ptr<NewTransformation>> transformations;

    //bool isDirty = true;
    glm::mat4 cachedMatrix = glm::mat4(1.0f);

public:
    void addTransformation(NewTransformation* transformation) {
        std::shared_ptr<NewTransformation> transformationShared(transformation);
        transformations.push_back(transformationShared);
        //isDirty = true;
    }

    void removeTransformation(int index) {
        if (index >= 0 && index < transformations.size()) {
            transformations.erase(transformations.begin() + index);
            //isDirty = true;
        }
    }

    void updateTransformation(int index, NewTransformation* newTransformation) {
        if (index >= 0 && index < transformations.size()) {
            transformations[index] = std::shared_ptr<NewTransformation>(newTransformation);
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

    NewTransformation* getTransformation(int index) {
        if (index >= 0 && index < transformations.size()) {
            return transformations[index].get();
        }
        return nullptr;
    }
};
