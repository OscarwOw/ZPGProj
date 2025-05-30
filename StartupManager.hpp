#ifndef STARTUP_MANAGER_HPP
#define STARTUP_MANAGER_HPP

#include <GL/glew.h>

#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class StartupManager {
private:
    StartupManager() {}

    StartupManager(const StartupManager&) = delete;
    StartupManager& operator=(const StartupManager&) = delete;

    GLFWwindow* _window;

public:
    static StartupManager& getInstance();

    int initializeProgram(GLFWwindow** window, int width, int height, const char* title);

    static void InitializeGLFW();
    static int InitializeGLEW(GLFWwindow* window);
    static void SetWindowHints();
    static GLFWwindow* CreateWindow(int width, int height, const char* title);
    static void DrawLegacyTriangles();
    static void PrintInfo();
    static void ViewPortSetup(GLFWwindow* window);

    GLFWwindow* getWindow();
};

#endif 