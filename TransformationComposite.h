#pragma once

#include "Transformation.h"

class TransformationComposite : public Transformation
{
private:
	std::vector <Transformation*> transformations;
public:
	void addTransformation(Transformation* t);
	void removeTransformations();
	void calculateTransformations();
	glm::mat4 resultMatrix();
	glm::mat4 getResultMatrix();
};

