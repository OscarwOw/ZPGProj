#pragma once
#include "IModel.h"

class TextureModel : public IModel {
public:
    TextureModel(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex)
        : _modelType(modelType), _vertexCount(vertexCount) {

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        _vertexBuffer = new VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));
        _vertexBuffer->Bind();

        unsigned int* indices = new unsigned int[vertexCount];
        for (int i = 0; i < vertexCount; ++i) {
            indices[i] = i;
        }
        _indexBuffer = new IndexBuffer(indices, vertexCount);
        delete[] indices;

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(6 * sizeof(float)));

        glBindVertexArray(0);
    }

    ~TextureModel() {
        delete _vertexBuffer;
        delete _indexBuffer;
        glDeleteVertexArrays(1, &_VAO);
    }

    void bind() override {
        glBindVertexArray(_VAO);
    }

    void unbind() override {
        glBindVertexArray(0);
    }

    ModelType getModelType() override {
        return _modelType;
    }

    int getVertexCount() override {
        return _vertexCount;
    }

private:
    ModelType _modelType;
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
};