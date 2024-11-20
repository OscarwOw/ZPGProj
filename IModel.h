#pragma once
#include "ModelType.h"


class IModel {
public:
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual ModelType getModelType() = 0;


};