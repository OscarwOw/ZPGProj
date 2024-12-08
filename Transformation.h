#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <glm/ext/matrix_transform.hpp>
#include "RandomMovementCube.h"
#include "IAnimationObject.h"
#include <glm/gtc/random.hpp>
#include "DynamicTranslateCubeData.h"

class Transformation {
public:
    virtual ~Transformation() = default;
    virtual glm::mat4 getMatrix() = 0; 
};