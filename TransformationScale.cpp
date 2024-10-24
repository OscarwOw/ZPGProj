#include "TransformationScale.h"

TransformationScale::TransformationScale(glm::vec3 scale)
{
	matrix = glm::scale(glm::mat4(1.0f), scale);
}

glm::mat4 TransformationScale::resultMatrix()
{
	return matrix;
}
