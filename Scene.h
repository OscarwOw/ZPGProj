#pragma once
#include "DrawableObject.h"
#include "LightSource.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    LightSource* _lightSource;
    bool _hasLightSource = false;
public:
    void addObject(DrawableObject* object);
    void drawScene();
    void clearScene();
    void addLightSource(LightSource* lightSource);
    LightSource* getLightSource();
    bool hasLightSource();
    void circusTransform();
    std::vector<DrawableObject*> getObjects();
};
