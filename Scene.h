#pragma once
#include "DrawableObject.h"
#include "LightSource.h"
#include "LightPublisher.h"
#include "BehaviorManager.h"
#include "skycube.h"
#include "ShaderProgramManager.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    std::vector<LightSource*> _lightSources;
    LightPublisher _lightPublisher;
    BehaviorManager* _behavioralManager;
    glm::vec3 _cameraPosition = glm::vec3(0.0f);
    glm::vec3 _cameraDirection = glm::vec3(0.0f,0.0f,1.0f);
    Texture* _skyboxTexture;
    ShaderProgram* _skyboxShaderProgram;
    unsigned int _skyboxVAO;
    unsigned int _skyboxVBO;

    bool _hasSkyBox = false;
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
    void addLightSource(ILightEmitter* lightSource);
    void addSkyBox(std::vector<std::string> faces);
    void drawSkybox();
    //std::vector<LightSource*> getLightSources();
    bool hasLightSource();
    void circusTransform();
    std::vector<DrawableObject*> getObjects();

    BehaviorManager* getBehavioralManager();
    void setBehavioralManager(BehaviorManager* behaviorManager);

    void setCameraDirection(glm::vec3 direction);
    void setCameraPosition(glm::vec3 position);
    glm::vec3 getCameraDirection();
    glm::vec3 getCameraPosition();
};
