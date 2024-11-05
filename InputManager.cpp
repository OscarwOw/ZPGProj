#include "InputManager.h"
#include "Application.h"

//Application& _application = Application::getInstance();

void InputManager::handleMovement(float time) {

    if (_forwardMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::FORWARD, time);
    }
    if (_leftMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::LEFT, time);
    }
    if (_backwardMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::BACKWARD, time);
    }
    if (_rightMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::RIGHT, time);
    }
    if (_upMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::UP, time);
    }
    if (_downMovement) {
        Camera::getInstance().processKeyboard(Camera_Movement::DOWN, time);
    }

    
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager& inputManager = InputManager::getInstance();
    if (key == GLFW_KEY_W && (action == GLFW_PRESS)) {
        inputManager._forwardMovement = true;
    }
    if (key == GLFW_KEY_W && (action == GLFW_RELEASE)) { 
        inputManager._forwardMovement = false;
    }

    if (key == GLFW_KEY_A && (action == GLFW_PRESS)) { 
        inputManager._leftMovement = true;
    }
    if (key == GLFW_KEY_A && (action == GLFW_RELEASE)) {  
        inputManager._leftMovement = false;
    }

    if (key == GLFW_KEY_S && (action == GLFW_PRESS)) { 
        inputManager._backwardMovement = true;
    }
    if (key == GLFW_KEY_S && (action == GLFW_RELEASE)) { 
        inputManager._backwardMovement = false;
    }

    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS)) {
        inputManager._upMovement = true;
    }
    if (key == GLFW_KEY_SPACE && (action == GLFW_RELEASE)) {
        inputManager._upMovement = false;
    }

    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS)) {
        inputManager._downMovement = true;
    }
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_RELEASE)) {
        inputManager._downMovement = false;
    }



    if (key == GLFW_KEY_D && (action == GLFW_PRESS)) {  
        inputManager._rightMovement = true;
    }
    if (key == GLFW_KEY_D && (action == GLFW_RELEASE)) { 
        inputManager._rightMovement = false;
    }

    if (key == GLFW_KEY_N && (action == GLFW_PRESS)) {
        SceneManager::getInstance().switchToNextScene();
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void InputManager::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {
    InputManager& inputManager = InputManager::getInstance();
    if (inputManager._mousePressed) {
        Camera::getInstance().processMouseMovement(mouseX - inputManager._lastMouseX, mouseY - inputManager._lastMouseY, false);
    }
    inputManager._lastMouseX = mouseX;
    inputManager._lastMouseY = mouseY;
}

void InputManager::mouse_button_pressed_callback(GLFWwindow* window, int button, int action, int mods) {
    InputManager& inputManager = InputManager::getInstance();
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        inputManager._mousePressed = true;
        printf("mouse pressed\n");
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
        printf("mouse released\n");
        inputManager._mousePressed = false;
    }
}

int InputManager::initializeEvents() {

    glfwSetCursorPosCallback(StartupManager::getInstance().getWindow(), cursor_pos_callback);
    glfwSetMouseButtonCallback(StartupManager::getInstance().getWindow(), mouse_button_pressed_callback);
    glfwSetKeyCallback(StartupManager::getInstance().getWindow(), key_callback);
    return 0;
}

