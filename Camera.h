#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ICameraObserver.h"
#include "CameraMovement.h"

class Camera {
public:
    static Camera& getInstance() {
        static Camera instance; 
        return instance;
    }

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    glm::mat4 getViewMatrix() const;

    glm::mat4 getPerspectiveMatrix() const;

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    void processMouseScroll(float yoffset);
    void attachObserver(ICameraObserver* observer);
    void detachObserver(ICameraObserver* observer);
    void setWindowSize(int width, int height);

    bool getLight();
    void setLight(bool light);

    glm::vec3 getCameraFront();

    void setPosition(const glm::vec3& newPosition);
    void setDirection(const glm::vec3& newDirection);



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

    bool _lightOn = true;

    int _windowHeight;
    int _windowWidth;

    // List of observers
    std::vector<ICameraObserver*> observers;
};

#endif // CAMERA_H
