#pragma once
#include "Scene.h"
#include "ShaderProgramManager.h"
#include "TransformationData.h"
#include "LightSource.h"
#include <cstdlib>
#include <ctime> 

#include "ShaderType.h"

#include "ModelMapping.h"

#include "DynamicTranslateCubeData.h"
#include "WhispData.h"
#include "ILightEmitter.h"
#include "DirectionalLightSource.h"`

class SceneGenerator {
public:
    static SceneGenerator& getInstance();

    Scene* generateDefaultScene();
    Scene* generateTestTreeScene();
    Scene* generateForestScene(int numTrees, float areaSize, float minDistance);
    Scene* generateNightForestScene(int numTrees, float areaSize, float minDistance);
    Scene* generateForestScene(int numTrees, int numBushes);
    Scene* generateSphereScene();

    Scene* generateShadersSphereScene();

    Scene* generateTextureScene();

    //DrawableObject* generateTree();
    //DrawableObject* generateTree(float scale, float rotation, float x, float z);

    LightSource* generateWhisp(Scene* scene, WhispData whispData);
    vector<LightSource*> generateWhisps(Scene* scene, int count);

    DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, MaterialProperties material, Texture* texture);

    DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, MaterialProperties material);

    DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color);

    DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType);

    DrawableObject* generateDrawableObject(ShaderType shaderType,const char* modelFile, Texture* texture, MaterialProperties material);

    //DrawableObject* generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType);
    LightSource* generateLightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, const glm::vec4& lightColor, float lightIntensity);
private:
    SceneGenerator() {}

    SceneGenerator(const SceneGenerator&) = delete;
    SceneGenerator& operator=(const SceneGenerator&) = delete;
    ShaderProgramManager& shaderProgramManager = ShaderProgramManager::getInstance();

    std::map<std::string, int> _namesIndexHolder;
};


