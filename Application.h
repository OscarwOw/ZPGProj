#pragma once
#include "SceneGenerator.h"
#include "SceneManager.h"
#include "ShaderProgramManager.h"
#include "StartupManager.hpp"
#include "Camera.h"

class Application {
public:
    static Application& getInstance();
    
    
    void cursor_callback(GLFWwindow* window, double x, double y);
    void button_callback(GLFWwindow* window, int button, int action, int mode);
    static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
    void movement_callback(GLFWwindow* window, float time);
    int startApplication();


private:    
    Application() {};
 

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;


    //singleton instances
    
    ShaderProgramManager& _shaderProgramManager = ShaderProgramManager::getInstance();
    SceneGenerator& _sceneGenerator = SceneGenerator::getInstance(); 
    SceneManager& _sceneManager = SceneManager::getInstance();
    StartupManager& _startupManager = StartupManager::getInstance();
    Camera& _camera = Camera::getInstance();    
};