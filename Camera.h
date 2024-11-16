#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ICameraObserver.h"
#include "CameraMovement.h"


// Camera class definition
class Camera {
public:
    static Camera& getInstance() {
        static Camera instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    // Delete copy constructor and assignment operator to prevent copies
    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;


    // Constructor with vectors


    // Get the view matrix
    glm::mat4 getViewMatrix() const;

    glm::mat4 getPerspectiveMatrix() const;

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);
    void attachObserver(ICameraObserver* observer);
    void detachObserver(ICameraObserver* observer);
    void setWindowSize(int width, int height);

    bool getLight();

    glm::vec3 getCameraFront();



private:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f);

    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch);


    void updateCameraVectors();
    void notifyObservers();

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    bool _lightOn = true;

    int _windowHeight;
    int _windowWidth;

    // List of observers
    std::vector<ICameraObserver*> observers;
};

#endif // CAMERA_H
