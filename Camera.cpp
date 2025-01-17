#include "Camera.h"
#include "MatrixHelper.h"

//AUTOR BEL0130

const float SPEED = 2.5f;
const float SENSITIVITY = 0.06f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

//Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
//    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY) {
//    position = glm::vec3(posX, posY, posZ);
//    worldUp = glm::vec3(upX, upY, upZ);
//    this->yaw = yaw;
//    this->pitch = pitch;
//    updateCameraVectors();
//}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}
glm::mat4 Camera::getPerspectiveMatrix() const {
    return glm::perspective(glm::radians(45.0f), (float)(_windowWidth / _windowHeight), 0.1f, 500.0f);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (false) { //real world movement
        if (direction == CameraMovement::FORWARD)
            position += glm::vec3(0.0f, 0.0f, 0.0f);
        if (direction == CameraMovement::BACKWARD)
            position -= 0.25 * velocity;
        if (direction == CameraMovement::LEFT)
            position[1] -= 0.25 * velocity;
        if (direction == CameraMovement::RIGHT)
            position[1] += 0.25 * velocity;
        if (direction == CameraMovement::UP)
            position[2] += 0.25 * velocity;
        if (direction == CameraMovement::DOWN)
            position[2] -= 0.25 * velocity;
    }
    else {
        if (direction == CameraMovement::FORWARD)
            position += front * velocity;
        if (direction == CameraMovement::BACKWARD)
            position -= front * velocity;
        if (direction == CameraMovement::LEFT)
            position -= right * velocity;
        if (direction == CameraMovement::RIGHT)
            position += right * velocity;
        if (direction == CameraMovement::UP)
            position += worldUp * velocity;
        if (direction == CameraMovement::DOWN)
            position -= worldUp * velocity;
    }

    notifyObservers();
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw -= xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateCameraVectors();
    notifyObservers();
}

void Camera::processMouseScroll(float yoffset) {
    movementSpeed += yoffset/2;
    //notifyObservers();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::notifyObservers() {
    glm::mat4 viewMatrix = getViewMatrix();
    glm::mat4 perspectiveMatrix = getPerspectiveMatrix();
    for (auto* observer : observers) {
        observer->setViewMatrix(viewMatrix);
        observer->setPerspectiveMatrix(perspectiveMatrix);
        observer->setCameraPosition(position);
    }
}

void Camera::attachObserver(ICameraObserver* observer) {
    observer->setPerspectiveMatrix(getPerspectiveMatrix());
    observer->setViewMatrix(getViewMatrix());
    observer->setCameraPosition(position);
    observers.push_back(observer);
}

void Camera::detachObserver(ICameraObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::setWindowSize(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
    notifyObservers();
}
bool Camera::getLight()
{
    return _lightOn;
}
void Camera::setLight(bool light)
{
    _lightOn = light;
}

glm::vec3 Camera::getCameraFront()
{
    return front;
}

void Camera::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    updateCameraVectors();
    notifyObservers();
}

// Set camera direction
void Camera::setDirection(const glm::vec3& newDirection) {
    front = glm::normalize(newDirection);

    pitch = glm::degrees(asin(front.y)); 

    if (front.x == 0.0f && front.z == 0.0f) {
        yaw = (front.y > 0.0f) ? 90.0f : -90.0f; 
    }
    else {
        yaw = glm::degrees(atan2(front.z, front.x)); 
    }

    updateCameraVectors();
    notifyObservers();
}

//
//void Camera::getWindowSize(int width, int height)
//{
//
//}
