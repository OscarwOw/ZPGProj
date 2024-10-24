#include "TransformationComposite.h"

void TransformationComposite::addTransformation(Transformation* t)
{
	transformations.push_back(t);
}

void TransformationComposite::removeTransformations()
{
	transformations.clear();
}

void TransformationComposite::calculateTransformations()
{
	this->matrix = glm::mat4(1.0f);

	for (auto t : transformations)
	{
		matrix = matrix * t->resultMatrix();
	}

	removeTransformations();
}

glm::mat4 TransformationComposite::resultMatrix()
{
	this->matrix = glm::mat4(1.0f);

	for (auto t : transformations)
	{
		this->matrix = this->matrix * t->resultMatrix();
	}

	return matrix;
}

glm::mat4 TransformationComposite::getResultMatrix()
{
	return this->matrix;
}
