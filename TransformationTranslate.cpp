#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(glm::vec3 translate)
{
	matrix = glm::translate(glm::mat4(1.0f), translate);
}

glm::mat4 TransformationTranslate::resultMatrix()
{
	return matrix;
}
