#pragma once
#include "Scene.h"
#include "ShaderProgramManager.h"
#include "TransformationData.h"
#include <cstdlib>
#include <ctime> 

#include "ShaderType.h"

#include "ModelMapping.h"


class SceneGenerator {
public:
    static SceneGenerator& getInstance();

    Scene* generateTraingleScene();
    Scene* generateTestTreeScene();
    Scene* generateForestScene(int numTrees, int numBushes);
    Scene* generateSphereScene();

    DrawableObject* generateTriangle(TransformationData transformationData);

    DrawableObject* generateTree();
    DrawableObject* generateTree(float scale, float rotation, float x, float z);

    DrawableObject* generateSphere(TransformationData transformationData);

    DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType);

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
