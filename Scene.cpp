#include "Scene.h"

void Scene::addObject(DrawableObject* obj) {
    objects.push_back(obj);
}

void Scene::drawScene() {
    for (auto& obj : objects) {
        obj->Draw(); 
    }
}

void Scene::clearScene() {
    for (auto& obj : objects) {
        delete obj;  
    }
    objects.clear(); 
}
