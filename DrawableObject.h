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
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include "TransformationRotate.h"
#include "TransformationDynamicRotate.h"
#include "TransformationDynamicTranslate.h"
#include "TransformationDynamicTranslateCube.h"
#include "TransformationBezier.h"


#include "TransformationComposite.h"
#include "Model.h"
#include "Texture.h"


//TODO this whole class is one big mess... should i call it mastershit?
class DrawableObject {

protected:
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    IModel* _model;
    Texture* _texture;
    
    
    ShaderProgram* _shaderProgram;
    std::string _shaderProgramManagerString;

    glm::vec3 _color = glm::vec3(0.01, 0.19, 0.12);

    MaterialProperties _materialProperties;

    glm::mat4 _transformationMatrix;

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
        MaterialProperties materialProperties = MaterialProperties(),
        Texture* texture = nullptr
    );
    DrawableObject(ShaderType shaderType,const char* modelFile, Texture* texture, MaterialProperties material);
    ~DrawableObject();
    //Transformation transformation;

    TransformationComposite transformationComposite;

    //void loadFromRawData(const float* rawData, int vertexCount, int stride);

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

    void updateDrawData();

    void updateTransformation(float deltaTime);
    //void printMatrix(const glm::mat4& matrix);
};
