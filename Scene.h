#pragma once
#include "DrawableObject.h"
#include "LightSource.h"
#include "LightPublisher.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    std::vector<LightSource*> _lightSources;
    LightPublisher _lightPublisher;
    //LightSource* _lightSource;
    bool _hasLightSource = false;
    void publishLights();
public:
    void addObject(DrawableObject* object);
    void addLightObserver(ILightObserver* observer);
    
    void drawScene();
    void clearScene();
    void addLightSource(LightSource* lightSource);
    std::vector<LightSource*> getLightSources();
    bool hasLightSource();
    void circusTransform();
    std::vector<DrawableObject*> getObjects();
};
