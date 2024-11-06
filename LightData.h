#pragma once
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/vector_float3.hpp>
struct LightData {
    glm::vec4 color;
    glm::vec3 position;
    bool hasLightColor,  hasLightPosition;

    LightData(const glm::vec4& lightColor, const glm::vec3& lightPosition)
        : color(lightColor), position(lightPosition),
        hasLightColor(true), hasLightPosition(true) {
    }
};