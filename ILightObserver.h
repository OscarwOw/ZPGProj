#pragma once
#include <glm/glm.hpp>
#include "LightData.h"
#include <vector>

class ILightObserver {
public:
    virtual void setLightsVector(std::vector<LightData> lightData) = 0;
};
