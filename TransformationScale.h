#pragma once

#include "Transformation.h"

class TransformationScale : public Transformation
{
public:
	TransformationScale(glm::vec3 scale);
	glm::mat4 resultMatrix();
};

