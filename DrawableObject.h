#pragma once
#include <vector>
#include "Mesh.h"
#include "TransformationComposite.h"
#include "ShaderProgram.h"

class DrawableObject {
private:
    std::vector<Mesh*> meshes;  // A collection of Mesh objects
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    

    ShaderProgram* _shaderProgram;

    //added for testing
    glm::mat4 _transformationMatrix;
    bool _isTransformationDirty;
    
    float _scaleFactor;
    GLuint _transformationUniformLocation;

    unsigned int* generateIndices(int vertexCount);

public:
    DrawableObject();
    ~DrawableObject();
    TransformationComposite transformationComposite;
    void addMesh(Mesh* mesh);

    void loadFromRawData(const float* rawData, int vertexCount, int stride);

    // Draw all the meshes
    void Draw();

    void setShaderProgram(ShaderProgram* shaderProgram);

    glm::mat4 GetCurrentTransformation();

    // Optional: Apply transformations to the entire object
    void translate(float x, float y, float z);
    void rotate(float angle, float x, float y, float z);
    void scale(float scale);
    void updateTransformation();
};
