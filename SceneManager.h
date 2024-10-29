#pragma once
#include <map>
#include <string>
#include "Scene.h"

class SceneManager {
private:
    std::map<std::string, Scene*> scenes;
    std::string currentSceneName;

    SceneManager() {}

    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
public:
    //SceneManager();
    static SceneManager& getInstance();

    void addScene(const std::string& name, Scene* scene);
    void switchScene(const std::string& name);
    Scene* getCurrentScene();
};
