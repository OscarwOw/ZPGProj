#pragma once
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_float3.hpp>
enum LightType {
    POINTLIGHT = 1,
    SPOTLIGHT = 2,
    DIRECTIONALLIGHT = 3
};

struct LightData {
    LightType lightType;
    
    
    glm::vec3 direction;
    float angle;
    
    glm::vec4 color;
    glm::vec3 position;
    bool hasLightColor,  hasLightPosition;


    LightData( const glm::vec4& lightColor, const glm::vec3& lightPosition)
        : color(lightColor), position(lightPosition),
        hasLightColor(true), hasLightPosition(true),
        lightType(POINTLIGHT)
    {
    }

    LightData(const glm::vec4& lightColor, const glm::vec3& lightPosition, const glm::vec3& lightDirection,float lightAngle)
        : color(lightColor), position(lightPosition),
        hasLightColor(true), hasLightPosition(true),
        lightType(SPOTLIGHT), angle(lightAngle),
        direction(lightDirection)
    {
    }

    LightData(LightType type, const glm::vec4& lightColor, const glm::vec3& lightDirection)
        : color(lightColor), direction(lightDirection),
        hasLightColor(true), hasLightPosition(true),
        lightType(DIRECTIONALLIGHT)
    {
    }

};

