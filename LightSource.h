#pragma once

#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <vector>
#include "ILightObserver.h"

class LightSource : public DrawableObject {
private:
    glm::vec4 _lightColor;            
    float _lightIntensity;            

public:
    LightSource(const DrawableObject& baseObject, const glm::vec4& lightColor, float lightIntensity)
        : DrawableObject(baseObject), _lightColor(lightColor), _lightIntensity(lightIntensity)
    {
        //TODO Reset the observer list to ensure it's empty.
    }
    LightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, const glm::vec4& lightColor, float lightIntensity);

    LightSource(const glm::vec3& position = glm::vec3(0.0f, 5.0f, 0.0f), const glm::vec4& color = glm::vec4(1.0f), float intensity = 1.0f) {
        translate(position.x, position.y, position.z);
        _lightColor = color;
        _lightIntensity = intensity;
    }
    void setLightColor(const glm::vec4& color);
    glm::vec4 getLightColor();
    void setLightIntensity(float intensity);
    float getLightIntensity();


    LightData getLightData();
};
