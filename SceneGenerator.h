#pragma once
#include "Scene.h"
#include "ShaderProgramManager.h"
#include "TransformationData.h"
#include <cstdlib>
#include <ctime> 
#include "tree.h"
#include "plain.h"

class SceneGenerator {
public:
    static SceneGenerator& getInstance();

    //void generateForest(Scene* scene, int numTrees, int numBushes, Camera* camera);
    Scene* generateTraingleScene();
    Scene* generateTestTreeScene();
    Scene* generateForestScene(int numTrees, int numBushes);

    DrawableObject* generateTriangle(TransformationData transformationData);

    DrawableObject* generateTree();
    DrawableObject* generateTree(float scale, float rotation, float x, float z);

    

    DrawableObject* generateBush();

private:
    SceneGenerator() {}

    SceneGenerator(const SceneGenerator&) = delete;
    SceneGenerator& operator=(const SceneGenerator&) = delete;
    ShaderProgramManager& shaderProgramManager = ShaderProgramManager::getInstance();
    void loadAndAttachTreeShader(DrawableObject* tree);

    void createShader(const std::string& shaderName, const std::string& shaderFilePath);

    std::map<std::string, int> _namesIndexHolder;

    

};
