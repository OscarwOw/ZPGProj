#include "Camera.h"
#include "MatrixHelper.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.06f;
const float ZOOM = 45.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}
glm::mat4 Camera::getPerspectiveMatrix() const {
    return glm::perspective(glm::radians(45.0f), (float)(_windowWidth / _windowHeight), 0.1f, 100.0f);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
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

    notifyObservers();
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw -= xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    updateCameraVectors();
    notifyObservers();
}

void Camera::processMouseScroll(float yoffset) {
    zoom -= yoffset;
    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 45.0f) zoom = 45.0f;
    notifyObservers();
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
//
//void Camera::getWindowSize(int width, int height)
//{
//
//}
