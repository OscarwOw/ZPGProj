#include "LightSource.h"

void LightSource::setLightColor(const glm::vec4& color) {
    _lightColor = color;
    notifyObservers();
}

glm::vec4 LightSource::getLightColor()
{
    return _lightColor;
}

void LightSource::setLightIntensity(float intensity) {
    _lightIntensity = intensity;
    notifyObservers();
}

float LightSource::getLightIntensity() {
    return _lightIntensity;
}

void LightSource::attachObserver(ILightObserver* observer) {
    _observers.push_back(observer);
    updateObserver(observer);
}

void LightSource::detachObserver(ILightObserver* observer) {
    _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}

void LightSource::notifyObservers() {
    for (ILightObserver* observer : _observers) {
        updateObserver(observer);
    }
}

void LightSource::updateObserver(ILightObserver* observer) {
    if (observer) {
        observer->updateLightColor(_lightColor);
        observer->updateLightIntensity(_lightIntensity);
        observer->updateLightPosition(glm::vec3(_transformationMatrix[3]));
    }
}