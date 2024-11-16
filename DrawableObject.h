#pragma once
#include <vector>
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>
#include "MatrixHelper.h"
#include "TransformationData.h"
#include "MaterialProperties.h"
#include "ShaderType.h"
#include "ModelType.h"
#include "Transformation.h"
#include "NewTransformation.h"
#include "NewTransformationComposite.h"
#include "Model.h"


//TODO this whole class is one big mess... should i call it mastershit?
class DrawableObject {
//TODO Transformation approach completly skip the composite patern and change it so that Transformation class is property of drawableObject
// so that we access it throught drawableObject.TransformationScale we gona have 3
// and we inherit 3 classes into Transformation.
// and then we have   

protected:
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    Model* _model;
    
    ShaderProgram* _shaderProgram;
    std::string _shaderProgramManagerString;

    glm::vec3 _color = glm::vec3(0.01, 0.19, 0.12);

    MaterialProperties _materialProperties;

    glm::mat4 _transformationMatrix;


    glm::mat4 _translationMatrix;
    glm::mat4 _scaleMatrix;
    glm::mat4 _rotationMatrix;

    TransformationData transformationData;
    
    float _scaleFactor;
    GLuint _transformationUniformLocation;

    unsigned int* generateIndices(int vertexCount);

public:
    DrawableObject();
    DrawableObject(
        TransformationData transformationData,
        ShaderType shaderType,
        ModelType modelType,
        glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
        MaterialProperties materialProperties = MaterialProperties()
    );
    ~DrawableObject();
    Transformation transformation;

    TransformationComposite transformationComposite;

    void loadFromRawData(const float* rawData, int vertexCount, int stride);

    // Draw all the meshes
    void Draw();

    void setShaderProgram(ShaderProgram* shaderProgram);
    void setShaderProgram(ShaderProgram* shaderProgram, std::string shaderProgramManagerString);
    void setColor(glm::vec3 color);
    glm::vec3 getColor();
    ShaderProgram* getSaherProgram();

    glm::mat4 GetCurrentTransformation();
    TransformationData GetCurrentTransformationData();
    glm::vec3 getPosition();

    MaterialProperties getMaterialProperties() const;

    // Optional: Apply transformations to the entire object
    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void scale(float scale);
    void updateDrawData();

    void updateTransformation(float deltaTime);
    //void printMatrix(const glm::mat4& matrix);
};
