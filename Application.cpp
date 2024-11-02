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


bool mousePressed = false;
double lastMouseX = 0;
double lastMouseY = 0;

bool wPressed, aPressed, sPressed, dPressed = false;



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
        if (key == GLFW_KEY_W && (action == GLFW_PRESS)) {
            wPressed = true;
        }
        if (key == GLFW_KEY_W && (action == GLFW_RELEASE)) {
            wPressed = false;
        }

        if (key == GLFW_KEY_A && (action == GLFW_PRESS)) {
            aPressed = true;
        }
        if (key == GLFW_KEY_A && (action == GLFW_RELEASE)) {
            aPressed = false;
        }

        if (key == GLFW_KEY_S && (action == GLFW_PRESS)) {
            sPressed = true;
        }
        if (key == GLFW_KEY_S && (action == GLFW_RELEASE)) {
            sPressed = false;
        }

        if (key == GLFW_KEY_D && (action == GLFW_PRESS)) {
            dPressed = true;
        }
        if (key == GLFW_KEY_D && (action == GLFW_RELEASE)) { 
            dPressed = false;
        }
    

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void mouse_button_pressed_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        mousePressed = true;
        printf("mouse pressed\n");
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        printf("mouse released\n");
        mousePressed = false;
    }
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    if (mousePressed) {
        Application::getInstance()._camera.processMouseMovement(mouseX - lastMouseX, mouseY - lastMouseY, false);
    }
    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

void Application::movement_callback(GLFWwindow* window, float time) {
    if (wPressed) {
        _camera.processKeyboard(Camera_Movement::FORWARD, time);
    }
    if (aPressed) {
        _camera.processKeyboard(Camera_Movement::LEFT, time);
    }
    if (sPressed) {
        _camera.processKeyboard(Camera_Movement::BACKWARD, time);
    }
    if (dPressed) {
        _camera.processKeyboard(Camera_Movement::RIGHT, time);
    }
}



//vertex buffer
//float points[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.5f, 0.5f, 0.0f,
//    -0.5f, 0.5f, 0.0f
//};
//
//unsigned int indices[] = {
//    0, 1, 2,
//    2, 3, 0
//};
//
//int counter = 0;



void tick(GLFWwindow* window, SceneManager& sceneManager) {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Get and draw the current scene
    Scene* currentScene = sceneManager.getCurrentScene();
    if (currentScene) {
        // Example of scene-specific transformation
        currentScene->circusTransform();
        currentScene->drawScene();
    }
    glfwSwapBuffers(window);

}


int Application::startApplication()
{
    glfwSetErrorCallback(error_callback);

    _startupManager.initializeProgram(&_window, 1500, 1200, "My OpenGL Window");

    _inputManager.initializeEvents();


    //glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)-> void {cursor_pos_callback(window, mouseXPos, mouseYPos); });

    //glfwSetMouseButtonCallback(_window, mouse_button_pressed_callback);

    //glfwSetWindowUserPointer(_window, &_camera);
    //glfwSetKeyCallback(_window, key_callback);

    ShaderProgramManager& shaderProgramManager = ShaderProgramManager::getInstance();
    SceneManager& sceneManager = SceneManager::getInstance();
    SceneGenerator& sceneGenerator = SceneGenerator::getInstance();

    /*Scene* forestScene = new Scene();
    sceneGenerator.generateForest(forestScene, 50, 25, &_camera);

    sceneManager.addScene("Forest", forestScene);
    sceneManager.switchScene("Forest");*/


    Scene* testscene = new Scene();
    DrawableObject* treeobj = sceneGenerator.generateTree(0.2f, 0.0f, 0.0f, 0.0f);
    //DrawableObject* treeobj1 = sceneGenerator.generateTree(0.1f, 45.0f, 0.5f, 3.0f);


    testscene->addObject(treeobj);
    //testscene->addObject(treeobj1);


    sceneManager.addScene("cirkus", testscene);
    sceneManager.switchScene("cirkus");

    //_camera->attachObserver(treeobj->getSaherProgram());
    _camera.attachObserver(treeobj->getSaherProgram());

    auto lastTickTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds tickInterval(16);
    auto movementCallbackTime = std::chrono::steady_clock::now();


    while (!glfwWindowShouldClose(_window)) {


        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickTime);


        // Check if 60 milliseconds have passed since the last tick
        if (elapsedTime >= tickInterval) {
            // Execute the tick function
            tick(_window, sceneManager);

            // Update the last tick time
            lastTickTime = currentTime;
        }
        currentTime = std::chrono::steady_clock::now();

        _inputManager.handleMovement(std::chrono::duration<float>(currentTime - movementCallbackTime).count());

        //movement_callback(_window, std::chrono::duration<float>(currentTime - movementCallbackTime).count());
        movementCallbackTime = currentTime;
        glfwPollEvents();
    }

    glfwDestroyWindow(_window);
    //shaderProgram->~ShaderProgram();
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}




