#include "Application.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <chrono>
Application& Application::getInstance()
{
    static Application instance;
    return instance;
}

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);

    Camera::getInstance().setWindowSize(width, height);
    glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


void tick(GLFWwindow* window, SceneManager& sceneManager, float deltatime) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get and draw the current scene
    Scene* currentScene = sceneManager.getCurrentScene();
    if (currentScene) {
        // Example of scene-specific transformation
        //currentScene->circusTransform();
        currentScene->drawScene(deltatime);
    }
    glfwSwapBuffers(window);

}


int Application::startApplication()
{
    glfwSetErrorCallback(error_callback);


    int width = 1500; //TODO from settings
    int height = 1200;

    _startupManager.initializeProgram(&_window, width, height, "My OpenGL Window");

    Camera::getInstance().setWindowSize(width, height);

    _inputManager.initializeEvents();


    glfwSetWindowSizeCallback(_window, window_size_callback);


    _sceneManager.generateTraingleScene("triangleScene");
    _sceneManager.generateForestScene("forestScene");

    _sceneManager.generateNightForestScene("nightForestScene");
    


    _sceneManager.generateSphereScene("sphereScene");
    _sceneManager.generateShadersSphereScene("shadersSphereScene");

    _sceneManager.switchScene("triangleScene");

    auto lastTickTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds tickInterval(16);
   /* const std::chrono::milliseconds tickInterval(100);*/
    auto movementCallbackTime = std::chrono::steady_clock::now();


    while (!glfwWindowShouldClose(_window)) {

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickTime);


        // Check if 60 milliseconds have passed since the last tick
        if (elapsedTime >= tickInterval) {
            // Execute the tick function
            tick(_window, _sceneManager, std::chrono::duration<float>(elapsedTime).count());

            // Update the last tick time
            lastTickTime = currentTime;
        }
        currentTime = std::chrono::steady_clock::now();

        _inputManager.handleMovement(std::chrono::duration<float>(currentTime - movementCallbackTime).count());

        movementCallbackTime = currentTime;
        glfwPollEvents();
    }

    glfwDestroyWindow(_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}






