#include "DirectionalLightSource.h"

void DirectionalLightSource::setDirection( glm::vec3& direction) {
    _direction = glm::normalize(direction);
}

glm::vec3 DirectionalLightSource::getDirection()  {
    return _direction;
}

void DirectionalLightSource::setLightColor( glm::vec4& color) {
    _lightColor = color;
}

glm::vec4 DirectionalLightSource::getLightColor()  {
    return _lightColor;
}

void DirectionalLightSource::setLightIntensity(float intensity) {
    _lightIntensity = intensity;
}

float DirectionalLightSource::getLightIntensity()  {
    return _lightIntensity;
}

LightData DirectionalLightSource::getLightData()  {
    return LightData(
        _lightColor,
        glm::normalize(_direction),
        _lightIntensity
    );
}
