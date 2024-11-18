#pragma once
#include "TransformationData.h"
#include "DynamicTranslateCubeData.h"
#include "LightData.h"


struct WhispData {
    TransformationData transformationData;
    DynamicTranslateCubeData dynamicTranslateCubeData;
    LightData lightData;

    WhispData(
        TransformationData& transformationData,
        DynamicTranslateCubeData& dynamicTranslateCubeData,
        LightData& lightData)
        : transformationData(transformationData),
        dynamicTranslateCubeData(dynamicTranslateCubeData),
        lightData(lightData)
    {
    }
};