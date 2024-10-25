#pragma once
#include "Scene.h"
#include "ShaderProgramManager.h"

class SceneGenerator {
public:
    static SceneGenerator& getInstance();

    void generateForest(Scene* scene, int numTrees, int numBushes);

    DrawableObject* generateTree();
    DrawableObject* generateTree(float scale, float rotation, float x, float z);

    DrawableObject* generateBush();

private:
    SceneGenerator() {}

    SceneGenerator(const SceneGenerator&) = delete;
    SceneGenerator& operator=(const SceneGenerator&) = delete;
    ShaderProgramManager& shaderProgramManager = ShaderProgramManager::getInstance();
    void loadAndAttachTreeShader(DrawableObject* tree);

};
