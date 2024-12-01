#pragma once
#include "ModelType.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class IModel {
public:
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual ModelType getModelType() = 0;
	virtual int getVertexCount() = 0;
	virtual void draw() = 0;

protected:
	ModelType _modelType;
	VertexBuffer* _vertexBuffer;
	IndexBuffer* _indexBuffer;
	GLuint _VAO;
	int _vertexCount;
};