#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class InputManager {
    public:
        static InputManager& getInstance() {
            static InputManager instance; 
            return instance;
        }

        InputManager(const InputManager&) = delete;
        InputManager& operator=(const InputManager&) = delete;
        int initializeEvents();    
    
        void handleMovement(float time);

        static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
        static void mouse_button_pressed_callback(GLFWwindow* window, int button, int action, int mods);

        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    private:
        InputManager() {}    

        bool _forwardMovement, _backwardMovement, _rightMovement, _leftMovement, _mousePressed, _upMovement, _downMovement = false;
        double _lastMouseX, _lastMouseY = 0;
};