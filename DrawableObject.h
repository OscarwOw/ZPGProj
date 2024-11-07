#pragma once
#include <vector>
#include "TransformationComposite.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>
#include "MatrixHelper.h"
#include "TransformationData.h"
#include "MaterialProperties.h"
#include "ShaderType.h"
#include "ModelType.h"


//TODO this whole class is one big mess... should i call it mastershit?
class DrawableObject {
    

protected:
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    
    ShaderProgram* _shaderProgram;
    std::string _shaderProgramManagerString;

    glm::vec3 _color = glm::vec3(0.01, 0.19, 0.12);

    MaterialProperties _materialProperties;

    //added for testing
    glm::mat4 _transformationMatrix;
    bool _isRotationTransformationDirty;
    bool _isScaleTransformationDirty;
    bool _isTranslateTransformationDirty;
    bool _isTransformationDirty;
                                  //if you change one all of them reset to default need to be addressed
                                 //idea is to have matrix and values of rotation, scale and translation. and when one is changed the other 2 will be used to calculate new matrix. 
                                 //proly other 2 flags need to be prepared dirtytranslate dirtyscale dirtyrotate
    
    Transformation* _curentTranslation;
    Transformation* _curentScale;
    Transformation* _curentRotation;

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
    void updateTransformation();
    //void printMatrix(const glm::mat4& matrix);
};
