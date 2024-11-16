#pragma once
#include <vector>
#include "DrawableObject.h"
#include "AnimationObject.h"
#include "IAnimationObject.h"

class BehaviorManager {
public:
    void addObject(AnimationObject* animationObject) {
        _objects.push_back(animationObject);
    }
    void addAnimeObject(IAnimationObject* animationObject) {
        _animeobjects.push_back(animationObject);
    }

    void update(float deltatime) {
        if (!_animeobjects.empty()) {
            for (IAnimationObject* object : _animeobjects) {
                if (object) {
                    object->update(deltatime);
                }
            }
        }        
        
        if (_objects.empty()) {
            return;  
        }
        for (AnimationObject* object : _objects) {
            if (object) {
                object->check();
            }
        }
    }

private:
	std::vector<AnimationObject*> _objects;
    std::vector<IAnimationObject*> _animeobjects;
};