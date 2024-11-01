#pragma once
#include <vector>
#include "TransformationComposite.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>
#include "MatrixHelper.h"

struct TransformationData{
    float TranslationX;
    float TranslationY;
    float TranslationZ;
    float RotationAngle;
    float RotationX;
    float RotationY;
    float RotationZ;
    float Scale;
};

class DrawableObject {
private:
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    
    ShaderProgram* _shaderProgram;
    std::string _shaderProgramManagerString;

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

    std::vector<glm::vec3> calculateNormals(const float* rawData, int vertexCount, int floatsPerVertex);

public:
    DrawableObject();
    ~DrawableObject();
    TransformationComposite transformationComposite;

    void loadFromRawData(const float* rawData, int vertexCount, int stride);

    // Draw all the meshes
    void Draw();

    void setShaderProgram(ShaderProgram* shaderProgram);
    void setShaderProgram(ShaderProgram* shaderProgram, std::string shaderProgramManagerString);
    ShaderProgram* getSaherProgram();

    glm::mat4 GetCurrentTransformation();
    TransformationData GetCurrentTransformationData();

    // Optional: Apply transformations to the entire object
    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void scale(float scale);
    void updateTransformation();
    //void printMatrix(const glm::mat4& matrix);
};
