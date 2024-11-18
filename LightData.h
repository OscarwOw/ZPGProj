#pragma once
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_float3.hpp>
#include "LightType.h"

struct LightData {
    LightType lightType; 
    glm::vec3 direction;
    float angle;
    
    glm::vec4 color;
    glm::vec3 position;

    float intensity;

    LightData( const glm::vec4& lightColor, const glm::vec3& lightPosition)
        : color(lightColor), position(lightPosition),
        lightType(POINTLIGHT)
    {
    }

    LightData(const glm::vec4& lightColor, const glm::vec3& lightPosition, const glm::vec3& lightDirection,float lightAngle)
        : color(lightColor), position(lightPosition),
        lightType(SPOTLIGHT), angle(lightAngle),
        direction(lightDirection)
    {
    }

    LightData(const glm::vec4& lightColor, const glm::vec3& lightDirection, float lightIntensity)
        : color(lightColor), direction(lightDirection), intensity(lightIntensity),
        lightType(DIRECTIONALLIGHT)
    {
    }
};

