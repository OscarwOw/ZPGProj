#pragma once
#include <map>
#include <string>
#include "Scene.h"
#include "SceneGenerator.h"

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
    Scene* generateTraingleScene(std::string name);
    Scene* generateTestTreeScene(std::string name);
    Scene* generateForestScene(std::string name);
    Scene* generateSphereScene(std::string name);
    Scene* generateShadersSphereScene(std::string name);
    void switchScene(const std::string& name);
    void rotateObjectSimulation();
    void switchToNextScene();
    std::string getNextScene();
    Scene* getCurrentScene();
};
