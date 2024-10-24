#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>  

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct Vertex {
	glm::vec4 position;
	glm::vec4 color;
};

class Mesh {
private:
    unsigned int VAO;
    VertexBuffer* _vertexBuffer;  // Pointer to VertexBuffer
    IndexBuffer* _indexBuffer;    // Pointer to IndexBuffer
    int vertexCount;
    GLenum drawMode;

public:
    // Constructor for mesh with index buffer
    Mesh(float* vertices, int vertexCount, unsigned int indices[], int indexCount, GLenum drawMode);
    Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, int floatsPerVertex, int startIndex, GLenum drawMode, unsigned int VAO);
    ~Mesh();

    // Set new vertex data
    void setVertices(Vertex a[], int vertexCount);

    // Set new index data
    void setIndices(unsigned int indices[], int indexCount);

    // Draw the mesh
    void DrawMesh();
};