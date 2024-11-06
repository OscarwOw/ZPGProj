#include "LightSource.h"

LightSource::LightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, const glm::vec4& lightColor, float lightIntensity)
    : DrawableObject(transformationData, shaderType, modelType, color), _lightColor(lightColor), _lightIntensity(lightIntensity) {
}

void LightSource::setLightColor(const glm::vec4& color) {
    _lightColor = color;
}

glm::vec4 LightSource::getLightColor()
{
    return _lightColor;
}

void LightSource::setLightIntensity(float intensity) {
    _lightIntensity = intensity;
}

float LightSource::getLightIntensity() {
    return _lightIntensity;
}

LightData LightSource::getLightData()
{
    return LightData(getLightColor(), getPosition());   
}
