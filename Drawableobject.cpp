#include "DrawableObject.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "TransformationRotate.h"
#include <glm/gtc/type_ptr.hpp> 


DrawableObject::DrawableObject() : _vertexBuffer(nullptr), _indexBuffer(nullptr), _isTransformationDirty(false) {
    _transformationMatrix = glm::mat4(1.0f);
}

DrawableObject::~DrawableObject() {
    delete _vertexBuffer;
    delete _indexBuffer;

    for (Mesh* mesh : meshes) {
        delete mesh;
    }
}

void DrawableObject::addMesh(Mesh* mesh) {
    meshes.push_back(mesh);
}

void DrawableObject::loadFromRawData(const float* rawData, int vertexCount, int floatsPerVertex)
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
    }
    
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);


}

void DrawableObject::setShaderProgram(ShaderProgram* shaderProgram) {
    _shaderProgram = shaderProgram;
}

glm::mat4 DrawableObject::GetCurrentTransformation() {
    return this->_transformationMatrix;
}


unsigned int* DrawableObject::generateIndices(int vertexCount) {
    unsigned int* indices = new unsigned int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        indices[i] = i;  
    }
    return indices;
}

void DrawableObject::translate(float x, float y, float z) {
    Transformation* translation = new TransformationTranslate(glm::vec3(x, y, z));
    transformationComposite.addTransformation(translation);
    _isTransformationDirty = true;
}

void DrawableObject::rotate(float angle, float x, float y, float z) {
    Transformation* rotation = new TransformationRotate(angle, glm::vec3(x, y, z));
    transformationComposite.addTransformation(rotation);
    _isTransformationDirty = true;
}

void DrawableObject::scale(float scaleFactor) {    
    Transformation* scale = new TransformationScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    transformationComposite.addTransformation(scale);
    _isTransformationDirty = true;
}

void DrawableObject::updateTransformation() {
    if (_isTransformationDirty) {
        transformationComposite.calculateTransformations();
        _transformationMatrix = transformationComposite.getResultMatrix();
        _isTransformationDirty = false;  
    }

    if (_shaderProgram) {
        _shaderProgram->use();
        _shaderProgram->setUniformMat4("u_TransformationMatrix", _transformationMatrix);
    }
}

