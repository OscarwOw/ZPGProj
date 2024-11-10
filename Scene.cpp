#include "Scene.h"

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
    addLightObserver(object->getSaherProgram());
}

void Scene::drawScene() {
    _behavioralManager->update();
    publishLights();
    for (auto& object : objects) {
        object->Draw(); 
    }
}

void Scene::clearScene() {
    for (auto& object : objects) {
        delete object;  
    }
    objects.clear(); 
}

void Scene::addLightObserver(ILightObserver* observer)
{
    _lightPublisher.attachObserver(observer);
    publishLights();
}

void Scene::publishLights()
{
    _lightPublisher.publish();
}

void Scene::addLightSource(LightSource* lightSource) {//TODO multiple light sources
    addObject(lightSource);
    _lightPublisher.attachLightSource(lightSource);
    _hasLightSource = true;
    publishLights();
}

std::vector<LightSource*> Scene::getLightSources() {
    return _lightSources;
}
bool Scene::hasLightSource() {
    return _hasLightSource;
}



void Scene::circusTransform()//deprecated
{
    TransformationData transformationdata = objects[0]->GetCurrentTransformationData();

    //objects[0]->getSaherProgram()->updatePerspective();


    if (transformationdata.RotationAngle < 360) {//(transformationdata.RotationAngle < 360.0f) {
        objects[0]->rotate(transformationdata.RotationAngle + 5.0f, transformationdata.RotationX,
                           transformationdata.RotationY, transformationdata.RotationZ);
        //objects[0]->translate(transformationdata.TranslationX + 0.005f, transformationdata.TranslationY , transformationdata.TranslationZ );
        //objects[0]->scale(0.3f );
    }
    else {
        objects[0]->rotate(0, transformationdata.RotationX,
                           transformationdata.RotationY, transformationdata.RotationZ);
        /*objects[0]->translate( 0, transformationdata.TranslationY, transformationdata.TranslationZ);*/

    }

}


std::vector<DrawableObject*> Scene::getObjects()
{
    return objects;
}

BehaviorManager* Scene::getBehavioralManager()
{
    return _behavioralManager;
}

void Scene::setBehavioralManager(BehaviorManager* behaviorManager)
{
    _behavioralManager = behaviorManager;
}
