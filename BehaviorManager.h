#pragma once
#include <vector>
#include "DrawableObject.h"
#include "AnimationObject.h"

class BehaviorManager {
public:
    void addObject(AnimationObject* animationObject) {
        _objects.push_back(animationObject);
    }

    void update() {
        for (AnimationObject* object : _objects) {
            if (object) {
                object->check();
            }
        }
    }

private:
	std::vector<AnimationObject*> _objects;
};