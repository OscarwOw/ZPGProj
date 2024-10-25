#include "SceneGenerator.h"
#include <cstdlib>
#include "tree.h"

SceneGenerator& SceneGenerator::getInstance()
{
    static SceneGenerator instance;
    return instance;
}

void SceneGenerator::generateForest(Scene* scene, int numTrees, int numBushes)
{
}

DrawableObject* SceneGenerator::generateTree()
{
    float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.5f) + 0.5f;
    float randomRotation = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
    float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f;
    float randomZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f;

    return generateTree(randomScale, randomRotation, randomX, randomZ);
}

DrawableObject* SceneGenerator::generateTree(float scale, float rotation, float x, float z) {
    DrawableObject* treeObject = new DrawableObject();
    
    loadAndAttachTreeShader(treeObject);
    treeObject->loadFromRawData(tree, 92814, 6);

    treeObject->scale(scale);
    treeObject->rotate(rotation, 0.0f, 1.0f, 0.0f);
    treeObject->translate(x, 0.0f, z);

    treeObject->updateTransformation();

    return treeObject;
}



void SceneGenerator::loadAndAttachTreeShader(DrawableObject* treeObject) {
    // Load the tree shader if it hasn't been loaded yet
    if (shaderProgramManager.getShader("treeShader") == nullptr) {
        shaderProgramManager.loadShader("treeShader", "tree.h");
    }

    // Attach the tree shader to the DrawableObject
    ShaderProgram* shader = shaderProgramManager.getShader("treeShader");
    if (shader) {
        treeObject->setShaderProgram(shader);
    }
}

DrawableObject* SceneGenerator::generateBush()
{
    return nullptr;
}
