#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "StartupManager.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <chrono>


#include "plain.h"
#include "tree.h"
#include "ErrorHandler.h"
#include "DrawableObject.h"
#include "SceneManager.h"
#include "SceneGenerator.h"
#include "ShaderProgramManager.h"


bool mousePressed = false;
double lastMouseX = 0;
double lastMouseY = 0;

bool wPressed, aPressed, sPressed, dPressed = false;

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (camera) {
        // Handle camera movement based on key input
        if (key == GLFW_KEY_W && (action == GLFW_PRESS )) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            wPressed = true;
        }
        if (key == GLFW_KEY_W && (action == GLFW_RELEASE)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            wPressed = false;
        }

        if (key == GLFW_KEY_A && (action == GLFW_PRESS)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            aPressed = true;
        }
        if (key == GLFW_KEY_A && (action == GLFW_RELEASE)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            aPressed = false;
        }

        if (key == GLFW_KEY_S && (action == GLFW_PRESS)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            sPressed = true;
        }
        if (key == GLFW_KEY_S && (action == GLFW_RELEASE)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            sPressed = false;
        }

        if (key == GLFW_KEY_D && (action == GLFW_PRESS)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            dPressed = true;
        }
        if (key == GLFW_KEY_D && (action == GLFW_RELEASE)) {
            //camera->processKeyboard(Camera_Movement::FORWARD, 0.1f);  
            dPressed = false;
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
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

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY) {    
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (mousePressed) {
        camera->processMouseMovement(mouseX - lastMouseX, mouseY - lastMouseY, false);
    }
    lastMouseX = mouseX;
    lastMouseY = mouseY;
}

static void movement_callback(GLFWwindow* window, float time) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (wPressed) {
        camera->processKeyboard(Camera_Movement::FORWARD, time);
    }
    if (aPressed) {
        camera->processKeyboard(Camera_Movement::LEFT, time);
    }
    if (sPressed) {
        camera->processKeyboard(Camera_Movement::BACKWARD, time);
    }
    if (dPressed) {
        camera->processKeyboard(Camera_Movement::RIGHT, time);
    }
}



//vertex buffer
float points[] = {
	 -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,	
	 0.5f, 0.5f, 0.0f,
    - 0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

int counter=0;



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



int main(void)
{
    glfwSetErrorCallback(error_callback);
    
    

    StartupManager::InitializeGLFW();
    StartupManager::SetWindowHints();
    GLFWwindow* window = StartupManager::CreateWindow(1500, 1200, "My OpenGL Window");

    if (StartupManager::InitializeGLEW(window) == -1)  return -1;

    StartupManager::PrintInfo();

    StartupManager::ViewPortSetup(window);

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)-> void {cursor_pos_callback(window, mouseXPos, mouseYPos); });

    glfwSetMouseButtonCallback(window, mouse_button_pressed_callback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //END OF OPENGL INIT


    Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetWindowUserPointer(window, camera);
    glfwSetKeyCallback(window, key_callback);

    ShaderProgramManager& shaderProgramManager = ShaderProgramManager::getInstance();
    SceneManager& sceneManager = SceneManager::getInstance();
    SceneGenerator& sceneGenerator = SceneGenerator::getInstance();

    Scene* forestScene = new Scene();
    sceneGenerator.generateForest(forestScene, 50, 25, camera);
    
    sceneManager.addScene("Forest", forestScene);
    sceneManager.switchScene("Forest");


    Scene* testscene = new Scene();
    DrawableObject* treeobj = sceneGenerator.generateTree(0.2f, 0.0f, 0.0f, 0.0f);
    //DrawableObject* treeobj1 = sceneGenerator.generateTree(0.1f, 45.0f, 0.5f, 3.0f);


    testscene->addObject(treeobj);
    //testscene->addObject(treeobj1);


    sceneManager.addScene("cirkus", testscene);
    sceneManager.switchScene("cirkus");

    camera->attachObserver(treeobj->getSaherProgram());


    
    //camera->processKeyboard(Camera_Movement::BACKWARD, 0.1f);

    auto lastTickTime = std::chrono::steady_clock::now();
    const std::chrono::milliseconds tickInterval(16);
    auto movementCallbackTime = std::chrono::steady_clock::now();


    while (!glfwWindowShouldClose(window)) {
        /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Scene* currentScene = sceneManager.getCurrentScene();
        if (currentScene) {
            
            //TODO some more logic
            currentScene->circusTransform();
            currentScene->drawScene();
        }

        glfwPollEvents();

        glfwSwapBuffers(window);*/


        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickTime);
        

        // Check if 60 milliseconds have passed since the last tick
        if (elapsedTime >= tickInterval) {
            // Execute the tick function
            tick(window, sceneManager);

            // Update the last tick time
            lastTickTime = currentTime;
        }
        currentTime = std::chrono::steady_clock::now();

        movement_callback(window, std::chrono::duration<float>(currentTime - movementCallbackTime).count());
        movementCallbackTime = currentTime;
        glfwPollEvents();

        

    }

    glfwDestroyWindow(window);
    //shaderProgram->~ShaderProgram();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
