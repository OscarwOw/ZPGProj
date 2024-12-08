#include "LightSource.h"

LightSource::LightSource(const glm::vec3& position, const glm::vec4& color, float intensity)
    : _lightColor(color), _lightIntensity(intensity), _lightType(POINTLIGHT)
{
}

LightSource::LightSource(const glm::vec3& position, const glm::vec4& color, float intensity, const glm::vec3& direction, float angle)
    : _lightColor(color), _lightIntensity(intensity), _direction(glm::normalize(direction)), _angle(angle), _lightType(SPOTLIGHT)
{
}

LightSource::LightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, const glm::vec4& lightColor, float lightIntensity, LightType lightType, const glm::vec3& direction, float angle)
    : DrawableObject(transformationData, shaderType, modelType, color), _lightColor(lightColor), _lightIntensity(lightIntensity), _lightType(lightType), _direction(glm::normalize(direction)), _angle(angle)
{
}

void LightSource::setLightColor(const glm::vec4& color) {
    _lightColor = color;
}

glm::vec4 LightSource::getLightColor() {
    return _lightColor;
}

void LightSource::setLightIntensity(float intensity) {
    _lightIntensity = intensity;
}

float LightSource::getLightIntensity() {
    return _lightIntensity;
}

void LightSource::setDirection(const glm::vec3& direction) {
    _direction = glm::normalize(direction);
}

glm::vec3 LightSource::getDirection() {
    return _direction;
}

void LightSource::setAngle(float angle) {
    _angle = angle;
}

float LightSource::getAngle() {
    return _angle;
}

void LightSource::setLightType(LightType type) {
    _lightType = type;
}

LightType LightSource::getLightType() {
    return _lightType;
}

LightData LightSource::getLightData() {
    if (_lightType == POINTLIGHT) {
        return LightData(getLightColor(), getPosition());
    }
    else if (_lightType == SPOTLIGHT) {
        return LightData(getLightColor(), getPosition(), getDirection(), getAngle());
    }

    // Fallback, in case of unexpected light type
    return LightData(getLightColor(), getPosition());
}
