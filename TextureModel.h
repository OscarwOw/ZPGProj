#pragma once
#include "IModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};


class TextureModel : public IModel {
public:
    TextureModel(ModelType modelType, const float* rawData, int vertexCount, int floatsPerVertex)
        : _modelType(modelType), _vertexCount(vertexCount) {

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        _vertexBuffer = new VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));
        _vertexBuffer->Bind();

        //unsigned int* indices = new unsigned int[vertexCount];
        //for (int i = 0; i < vertexCount; ++i) {
        //    indices[i] = i;
        //}
        //_indexBuffer = new IndexBuffer(indices, vertexCount);
        //delete[] indices;

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, floatsPerVertex * sizeof(float), (void*)(6 * sizeof(float)));

        _hasIBO = false;

        glBindVertexArray(0);
    }

    TextureModel(const char* modelFile) {
        Assimp::Importer importer;
        unsigned int importOptions = aiProcess_Triangulate //Converts polygons to triangles
            | aiProcess_OptimizeMeshes              // Reduces the number of submeshes
            | aiProcess_JoinIdenticalVertices       // Removes duplicate vertices
            | aiProcess_CalcTangentSpace;           // Computes tangents and bitangents

        //aiProcess_GenNormals/ai_Process_GenSmoothNormals - Generates flat/Smooth normals

        const aiScene* scene = importer.ReadFile(modelFile, importOptions);
        _hasIBO = true;


        if (scene) {
            printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
            printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);
            for (unsigned int i = 0; i < scene->mNumMaterials; i++)
            {
                const aiMaterial* mat = scene->mMaterials[i];
                aiString name;
                mat->Get(AI_MATKEY_NAME, name);
                printf("Material [%d] name %s\n", i, name.C_Str());
                aiColor4D d;
                glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
                if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                    diffuse = glm::vec4(d.r, d.g, d.b, d.a);
            }


            for (unsigned int i = 0; i < scene->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[i];
                Vertex* pVertices = new Vertex[mesh->mNumVertices];
                std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
                for (unsigned int i = 0; i < mesh->mNumVertices; i++)
                {
                    if (mesh->HasPositions()) {
                        pVertices[i].Position[0] = mesh->mVertices[i].x;
                        pVertices[i].Position[1] = mesh->mVertices[i].y;
                        pVertices[i].Position[2] = mesh->mVertices[i].z;
                    }

                    if (mesh->HasNormals()) {
                        pVertices[i].Normal[0] = mesh->mNormals[i].x;
                        pVertices[i].Normal[1] = mesh->mNormals[i].y;
                        pVertices[i].Normal[2] = mesh->mNormals[i].z;
                    }

                    if (mesh->HasTextureCoords(0)) {
                        pVertices[i].Texture[0] = mesh->mTextureCoords[0][i].x;
                        pVertices[i].Texture[1] = mesh->mTextureCoords[0][i].y;
                    }

                    if (mesh->HasTangentsAndBitangents()) {
                        pVertices[i].Tangent[0] = mesh->mTangents[i].x;
                        pVertices[i].Tangent[1] = mesh->mTangents[i].y;
                        pVertices[i].Tangent[2] = mesh->mTangents[i].z;
                    }
                }

                unsigned int* pIndices = nullptr;
                if (mesh->HasFaces()) {
                    pIndices = new unsigned int[mesh->mNumFaces * 3];
                    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
                        pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                        pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                        pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                    }
                }

                glGenVertexArrays(1, &_VAO);

                //GLuint VBO = 0;
                //glGenBuffers(1, &VBO);

                GLuint IBO = 0;
                glGenBuffers(1, &IBO);

                glBindVertexArray(_VAO);


                _vertexBuffer = new VertexBuffer(pVertices, sizeof(Vertex) * mesh->mNumVertices);
                //VertexBuffer(rawData, vertexCount * floatsPerVertex * sizeof(float));

                //glBindBuffer(GL_ARRAY_BUFFER, VBO);
                //glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
                glEnableVertexAttribArray(2);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));

                //Tangent for Normal Map
                glEnableVertexAttribArray(3);
                glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));


                //Index Buffer
                _indexBuffer = new IndexBuffer(pIndices, sizeof(GLuint) * mesh->mNumFaces * 3);
                //_indexBuffer = new IndexBuffer(indices, vertexCount);

                //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
                //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindVertexArray(_VAO);

                GLuint err = glGetError();
                if (err != GL_NO_ERROR) {
                    std::cout << "GL ERROR: " << err << std::endl;
                }
                _vertexCount = mesh->mNumFaces * 3;
                
                delete[] pVertices;
                delete[] pIndices;
            }


        }
    }

    ~TextureModel() {
        delete _vertexBuffer;
        if (_hasIBO) {
            delete _indexBuffer;
        }
        glDeleteVertexArrays(1, &_VAO);
    }

    void bind() override {
        glBindVertexArray(_VAO);
    }

    void unbind() override {
        glBindVertexArray(0);
    }

    ModelType getModelType() override {
        return _modelType;
    }

    int getVertexCount() override {
        return _vertexCount;
    }
    void draw() override {
        bind();
        if (_hasIBO) {
            glDrawElements(GL_TRIANGLES, _vertexCount, GL_UNSIGNED_INT, nullptr);
        }
        else {
            glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
        }
        unbind();
    }

private:
    ModelType _modelType;
    VertexBuffer* _vertexBuffer;
    IndexBuffer* _indexBuffer;
    GLuint _VAO;
    int _vertexCount;
    bool _hasIBO;
};