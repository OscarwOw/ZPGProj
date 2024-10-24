#include "DrawableObject.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "TransformationRotate.h"
#include <glm/gtc/type_ptr.hpp> 


DrawableObject::DrawableObject() : _vertexBuffer(nullptr), _indexBuffer(nullptr) {
}

DrawableObject::~DrawableObject() {
    // Clean up vertex and index buffers
    delete _vertexBuffer;
    delete _indexBuffer;

    // Clean up all the meshes
    for (Mesh* mesh : meshes) {
        delete mesh;
    }
}

void DrawableObject::addMesh(Mesh* mesh) {
    meshes.push_back(mesh);  // Add a mesh to the list
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


unsigned int* DrawableObject::generateIndices(int vertexCount) {
    unsigned int* indices = new unsigned int[vertexCount];
    for (int i = 0; i < vertexCount; ++i) {
        indices[i] = i;  
    }
    return indices;
}

// Optional: Implement transformation methods here
// For example, using glm::translate, glm::rotate, glm::scale, etc.
void DrawableObject::translate(float x, float y, float z) {
    Transformation* translation = new TransformationTranslate(glm::vec3(x, y, z));
    transformationComposite.addTransformation(translation);
}

void DrawableObject::rotate(float angle, float x, float y, float z) {
    Transformation* rotation = new TransformationRotate(angle, glm::vec3(x, y, z));
    transformationComposite.addTransformation(rotation);
}

void DrawableObject::scale(float scaleFactor) {    
    Transformation* scale = new TransformationScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
    transformationComposite.addTransformation(scale);

    /*_scaleFactor = scaleFactor;
    _transformationMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(_scaleFactor, _scaleFactor, _scaleFactor));
    */
}

void DrawableObject::updateTransformation() {
    transformationComposite.calculateTransformations();
    glm::mat4 finalMatrix = transformationComposite.getResultMatrix();

    if (_shaderProgram) {
        _shaderProgram->use();
        _shaderProgram->setUniformMat4("u_TransformationMatrix", finalMatrix);
    }
}

