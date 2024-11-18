#pragma once
#include "LightData.h"

// Interface class for light emitters
class ILightEmitter {
public:
    virtual LightData getLightData() = 0;

    virtual ~ILightEmitter() {}
};
