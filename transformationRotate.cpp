#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(float angle, glm::vec3 axis)
{
	float r = glm::radians(angle);
	matrix = glm::rotate(glm::mat4(1.0), r, axis);
}

glm::mat4 TransformationRotate::resultMatrix()
{
	return matrix;
}
