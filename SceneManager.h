#pragma once
#include "Scene.h"

class SceneManager {
private:
    std::vector<Scene*> scenes;
    int currentSceneIndex;

    SceneManager() : currentSceneIndex(0) {}

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
public:
    //SceneManager();
    static SceneManager& getInstance();
    void addScene(Scene* scene);
    void switchScene(int index);
    Scene* getCurrentScene();
};
