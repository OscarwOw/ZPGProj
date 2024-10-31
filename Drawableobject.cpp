#include "DrawableObject.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "TransformationRotate.h"
#include <glm/gtc/type_ptr.hpp> 


DrawableObject::DrawableObject() : _vertexBuffer(nullptr), _indexBuffer(nullptr), _isTransformationDirty(false) {
    _transformationMatrix = glm::mat4(1.0f);
    _translationMatrix = glm::mat4(1.0f);
    _rotationMatrix = glm::mat4(1.0f);
    _scaleMatrix = glm::mat4(1.0f);
   //_matrixHelperInstance = MatrixHelper::getInstance();
}

DrawableObject::~DrawableObject() {
    delete _vertexBuffer;
    delete _indexBuffer;

}

void DrawableObject::loadFromRawData(const float* rawData, int vertexCount, int floatsPerVertex) //TODO RawDataLoader
{
    _vertexCount = vertexCount;

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);


    _vertexBuffer = new VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));
    _indexBuffer = new IndexBuffer(generateIndices(vertexCount), vertexCount);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));   

    glBindVertexArray(0);
}

void DrawableObject::Draw() {
    if (_shaderProgram) {
        updateTransformation();
        _shaderProgram->use();
    }
    
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void DrawableObject::setShaderProgram(ShaderProgram* shaderProgram) { 
    _shaderProgram = shaderProgram;
}

void DrawableObject::setShaderProgram(ShaderProgram* shaderProgram, std::string shaderProgramManagerString) {
    _shaderProgram = shaderProgram;
    _shaderProgramManagerString = shaderProgramManagerString;
}

ShaderProgram* DrawableObject::getSaherProgram()
{
    if (_shaderProgram) {
        return _shaderProgram;
    }
    return nullptr;
}

glm::mat4 DrawableObject::GetCurrentTransformation() {
    return this->_transformationMatrix;
}

TransformationData DrawableObject::GetCurrentTransformationData() {
    return transformationData;
}

unsigned int* DrawableObject::generateIndices(int vertexCount) {
    unsigned int* indices = new unsigned int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        indices[i] = i;  
    }
    return indices;
}

void DrawableObject::translate(float x, float y, float z) {
    _translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

    
    transformationData.TranslationX = x;
    transformationData.TranslationY = y;
    transformationData.TranslationZ = z;


    _isTranslateTransformationDirty = true;
    _isTransformationDirty = true;
}

void DrawableObject::rotate(float angle, float x, float y, float z) {
    _rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(x, y, z));

    transformationData.RotationAngle = angle;
    transformationData.RotationX = x;
    transformationData.RotationY = y;
    transformationData.RotationZ = z;

    _isRotationTransformationDirty = true;
    _isTransformationDirty = true;
}

void DrawableObject::scale(float scaleFactor) {    
    //Transformation* scale = new TransformationScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    //transformationComposite.addTransformation(scale);
    //_curentScale = scale;

    _scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor, scaleFactor, scaleFactor));

    transformationData.Scale = scaleFactor;

    _isScaleTransformationDirty = true;
    _isTransformationDirty = true;
}

void DrawableObject::updateTransformation() {
    MatrixHelper& matrixHelper = MatrixHelper::getInstance();

    glm::mat4 modelMatrix = _translationMatrix * _rotationMatrix * _scaleMatrix;

    glm::mat4 viewMatrix = glm::mat4(1.0);
    glm::mat4 perspectiveMatrix = glm::mat4(1.0);

    //glm::mat4 CompareViewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -0.0f, 0.0f));
    //perspectiveMatrix = glm::perspective(glm::radians(45.0f), (float)(1500/ 1200), 0.1f, 100.0f);


    if (_shaderProgram) {
        _shaderProgram->use();
        _shaderProgram->setUniformMat4("modelMatrix", modelMatrix);
    }

    if (_shaderProgram) {
        _shaderProgram->use();
        viewMatrix = _shaderProgram->getViewMatrix();

        
        
        /*
        printf("view matrix woooooo: \n");

        matrixHelper.printMatrix(viewMatrix);*/

        _shaderProgram->setUniformMat4("viewMatrix", viewMatrix);
    }
    if (_shaderProgram) {
        _shaderProgram->use();

        perspectiveMatrix = _shaderProgram->getPerspectiveMatrix();

        _shaderProgram->setUniformMat4("projectionMatrix", perspectiveMatrix);
    }

    
   
}


