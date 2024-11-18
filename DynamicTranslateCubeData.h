#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct DynamicTranslateCubeData {
    float speed;
    float cubeSize;
    glm::mat4 initialMatrix;
    float maxHeight;
    float maxWidth;
    float maxLength;
    float minHeight;
    float minWidth;
    float minLength;

    // Constructor with all values
    DynamicTranslateCubeData(
        float speed,
        float cubeSize,
        glm::mat4 initialMatrix,
        float maxHeight,
        float maxWidth,
        float maxLength,
        float minHeight,
        float minWidth,
        float minLength
    ) : speed(speed),
        cubeSize(cubeSize),
        initialMatrix(initialMatrix),
        maxHeight(maxHeight),
        maxWidth(maxWidth),
        maxLength(maxLength),
        minHeight(minHeight),
        minWidth(minWidth),
        minLength(minLength)
    {
    }
};
