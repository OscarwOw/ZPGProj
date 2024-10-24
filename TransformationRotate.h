#pragma once

#include "Transformation.h"

class TransformationRotate : public Transformation
{
public:
	TransformationRotate(float angle, glm::vec3 axis);
	glm::mat4 resultMatrix();
};