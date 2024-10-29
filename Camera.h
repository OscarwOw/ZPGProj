#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Defines several possible options for camera movement.
enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class ICameraObserver {
public:
    virtual void updateViewMatrix(const glm::mat4& viewMatrix) = 0;
    virtual void updatePerspectiveMatrix(const glm::mat4& viewMatrix) = 0;
};

// Camera class definition
class Camera {
public:
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f);

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch);

    // Get the view matrix
    glm::mat4 getViewMatrix() const;

    glm::mat4 getPerspectiveMatrix() const;

    // Process keyboard input
    void processKeyboard(Camera_Movement direction, float deltaTime);

    // Process mouse movement
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // Process mouse scroll
    void processMouseScroll(float yoffset);

    // Attach observer
    void attachObserver(ICameraObserver* observer);

    // Detach observer
    void detachObserver(ICameraObserver* observer);

private:
    // Update the camera vectors based on yaw and pitch
    void updateCameraVectors();

    // Notify observers about the view matrix update
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

    // List of observers
    std::vector<ICameraObserver*> observers;
};

#endif // CAMERA_H
