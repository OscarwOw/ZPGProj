#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ModelType.h"
#include "IModel.h"


class Model : public IModel {
public:
    Model(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex)
        : _modelType(modelType), _vertexCount(vertexCount) {
        //_hasIBO = false;
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        _vertexBuffer = new VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));
        _vertexBuffer->Bind();

        //unsigned int* indices = new unsigned int[vertexCount];
        //for (int i = 0; i < vertexCount; ++i) {
        //    indices[i] = i;
        //}
        //_indexBuffer = new IndexBuffer(indices, vertexCount);
        //delete[] indices;

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));

        glBindVertexArray(0);
    }

    ~Model() {
        delete _vertexBuffer;
        //delete _indexBuffer;
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
    void draw() override {
        bind();
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
        unbind();
    }

private:
    ModelType _modelType;
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    //bool _hasIBO;
};
