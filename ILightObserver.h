#pragma once
#include <glm/glm.hpp>

class ILightObserver {
public:

    virtual void setLightColor(const glm::vec4& color) = 0;
    virtual void setLightIntensity(float intensity) = 0;
    virtual void setLightPosition(const glm::vec3& position) = 0;
};
