#include "Mesh.h"
#include <iostream>

// Constructor: initialize VAO, VBO, and EBO using VertexBuffer and IndexBuffer
Mesh::Mesh(float* vertices, int vertexCount, unsigned int indices[], int indexCount, GLenum drawMode)
    : vertexCount(vertexCount), drawMode(drawMode)
{

    std::cout << "Mesh created with " << vertexCount << " vertices." << std::endl;
    for (int i = 0; i < vertexCount; ++i) {
        std::cout << "Vertex " << i << ": ("
            << vertices[i * 6] << ", "       // x position
            << vertices[i * 6 + 1] << ", "   // y position
            << vertices[i * 6 + 2] << ") "   // z position
            << "Color: ("
            << vertices[i * 6 + 3] << ", "   // r color
            << vertices[i * 6 + 4] << ", "   // g color
            << vertices[i * 6 + 5] << ")"    // b color
            << std::endl;
    }

    // Generate and bind the Vertex Array Object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind VertexBuffer
    _vertexBuffer = new VertexBuffer(vertices, vertexCount * sizeof(float) * 3);

    // Set up vertex attributes (position and color)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // Create and bind IndexBuffer
    _indexBuffer = new IndexBuffer(indices, indexCount);

    // Unbind the VAO to prevent accidental modifications
    glBindVertexArray(0);
}

Mesh::Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, int floatsPerVertex, int startIndex, GLenum drawMode, unsigned int VAO)
    : drawMode(drawMode), VAO(VAO)
{
    _vertexBuffer = vertexBuffer;
    _indexBuffer = indexBuffer;


}

// Destructor: clean up buffers
Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    delete _vertexBuffer;
    delete _indexBuffer;
}

// Set new vertices (re-upload data to the VertexBuffer)
void Mesh::setVertices(Vertex a[], int vertexCount) {
    _vertexBuffer->Bind();
    _vertexBuffer->setData(a, vertexCount * sizeof(Vertex));
    _vertexBuffer->unbind();
}

// Set new indices (re-upload data to the IndexBuffer)
void Mesh::setIndices(unsigned int indices[], int indexCount) {
    _indexBuffer->Bind();
    _indexBuffer->setData(indices, indexCount * sizeof(unsigned int));
    _indexBuffer->unbind();
}

// Draw the mesh using index buffer
void Mesh::DrawMesh() {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the IndexBuffer
    _indexBuffer->Bind();

    // Draw the elements using indices
    glDrawElements(drawMode, _indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

    // Unbind the VAO
    glBindVertexArray(0);
}
