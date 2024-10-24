#pragma once

#include "Transformation.h"

class TransformationTranslate : public Transformation
{
public:
	TransformationTranslate(glm::vec3 translate);
	glm::mat4 resultMatrix();
};

