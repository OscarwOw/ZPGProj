#pragma once
#include "DrawableObject.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
public:
    void addObject(DrawableObject* obj);
    void drawScene();
    void clearScene();
    void circusTransform();
    std::vector<DrawableObject*> getObjects();
};
