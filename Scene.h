#pragma once
#include "DrawableObject.h"
#include "LightSource.h"
#include "LightPublisher.h"
#include "BehaviorManager.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    std::vector<LightSource*> _lightSources;
    LightPublisher _lightPublisher;
    BehaviorManager* _behavioralManager;
    //LightSource* _lightSource;
    bool _hasLightSource = false;
    void publishLights();
public:
    Scene() {
        setBehavioralManager(new BehaviorManager());
    }
    void addObject(DrawableObject* object);
    void addLightObserver(ILightObserver* observer);
    
    void drawScene(float deltatime);
    void clearScene();
    void addLightSource(LightSource* lightSource);
    std::vector<LightSource*> getLightSources();
    bool hasLightSource();
    void circusTransform();
    std::vector<DrawableObject*> getObjects();

    BehaviorManager* getBehavioralManager();
    void setBehavioralManager(BehaviorManager* behaviorManager);
};
