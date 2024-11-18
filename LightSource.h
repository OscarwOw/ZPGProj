#pragma once

#include "DrawableObject.h"
#include <glm/glm.hpp>
#include <vector>
#include "ILightObserver.h"
#include "LightType.h"
#include "ILightEmitter.h"

class LightSource : public DrawableObject, public ILightEmitter {
private:
    glm::vec4 _lightColor;
    float _lightIntensity;
    glm::vec3 _direction; // Direction for Spotlights and Directional Lights
    float _angle;          // Cutoff angle for Spotlights
    LightType _lightType;  // Type of the light (Point, Spotlight, Directional)

public:
    // Constructor for Point Light
    LightSource(const glm::vec3& position = glm::vec3(0.0f, 5.0f, 0.0f), const glm::vec4& color = glm::vec4(1.0f), float intensity = 1.0f);

    // Constructor for Spot Light
    LightSource(const glm::vec3& position, const glm::vec4& color, float intensity, const glm::vec3& direction, float angle);

    // Constructor for Directional Light
    LightSource(const glm::vec4& color, float intensity, const glm::vec3& direction);

    // Constructor for LightSource with DrawableObject base
    LightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, const glm::vec4& lightColor, float lightIntensity, LightType lightType = POINTLIGHT, const glm::vec3& direction = glm::vec3(0.0f), float angle = 0.0f);

    void setLightColor(const glm::vec4& color);
    glm::vec4 getLightColor();
    void setLightIntensity(float intensity);
    float getLightIntensity();
    void setDirection(const glm::vec3& direction);
    glm::vec3 getDirection();
    void setAngle(float angle);
    float getAngle();
    void setLightType(LightType type);
    LightType getLightType();

    LightData getLightData() override;
};
