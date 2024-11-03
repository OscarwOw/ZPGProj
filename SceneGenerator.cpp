#pragma once
#include "SceneGenerator.h"


SceneGenerator& SceneGenerator::getInstance()
{
    static SceneGenerator instance;
    return instance;
}

#pragma region scene generation functions 
Scene* SceneGenerator::generateDefaultScene() {
    Scene* scene = new Scene(); 
    TransformationData transformationData;
    //transformationData.TranslationX = -2.0f;
    transformationData.TranslationZ = -2.0f;
    DrawableObject* triangle = generateDrawableObject(transformationData, ShaderType::Test, ModelType::TRIANGLE);
    scene->addObject(triangle);


    transformationData.TranslationX = -2.0f;
    transformationData.TranslationY = 2.0f;
    transformationData.TranslationZ = 0.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Test, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light);

    return scene;
}

Scene* SceneGenerator::generateTestTreeScene()
{
    Scene* scene = new Scene();
    TransformationData transformationData;
    DrawableObject* tree = generateDrawableObject(transformationData, ShaderType::Test, ModelType::TREE);

    scene->addObject(tree);
    return scene;
}

Scene* SceneGenerator::generateForestScene(int numTrees, float areaSize, float minDistance) {
    Scene* forestScene = new Scene();

    std::vector<glm::vec3> treePositions;

    for (int i = 0; i < numTrees; ++i) {
        glm::vec3 position;

        bool validPosition = false;

        int currentDepth = 0;
        int stackOverflowDepth = 128;
        while (!validPosition && currentDepth < stackOverflowDepth) {
            float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / areaSize) - (areaSize / 2);
            float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / areaSize) - (areaSize / 2);
            float y = 0.0f; 

            position = glm::vec3(x, y, z);
            validPosition = true;
            currentDepth++;
            for (const auto& existingPosition : treePositions) {
                if (glm::distance(existingPosition, position) < minDistance) {
                    validPosition = false;
                    break;
                }
            }
        }

        treePositions.push_back(position);

        TransformationData treeTransformationData;
        treeTransformationData.TranslationX = position.x;
        treeTransformationData.TranslationY = position.y;
        treeTransformationData.TranslationZ = position.z;
        treeTransformationData.Scale = 1.0f;
        treeTransformationData.RotationAngle = 0.0f; 

        DrawableObject* tree = generateDrawableObject(treeTransformationData, ShaderType::Test, ModelType::TREE);

        forestScene->addObject(tree);

        int numBushes = rand() % 3;
        for (int j = 0; j < numBushes; ++j) {
            float bushOffsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / minDistance) - (minDistance / 2);
            float bushOffsetZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / minDistance) - (minDistance / 2);

            glm::vec3 bushPosition = position + glm::vec3(bushOffsetX, 0.0f, bushOffsetZ);

            TransformationData bushTransformationData;
            bushTransformationData.TranslationX = bushPosition.x;
            bushTransformationData.TranslationY = bushPosition.y;
            bushTransformationData.TranslationZ = bushPosition.z;
            bushTransformationData.Scale = 0.5f; 
            bushTransformationData.RotationAngle = 0.0f; 

            DrawableObject* bush = generateDrawableObject(bushTransformationData, ShaderType::Test, ModelType::BUSH);

            forestScene->addObject(bush);
        }
    }
    TransformationData transformationData;
    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 0.0f;
    transformationData.TranslationZ = -8.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Test, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    forestScene->addLightSource(light);
    forestScene->addObject(light);
    return forestScene;
}


Scene* SceneGenerator::generateSphereScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;
    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere1 = generateDrawableObject(transformationData, ShaderType::Test, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere2 = generateDrawableObject(transformationData, ShaderType::Test, ModelType::SPHERE);

    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere3 = generateDrawableObject(transformationData, ShaderType::Test, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere4 = generateDrawableObject(transformationData, ShaderType::Test, ModelType::SPHERE);

    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 0.0f;
    transformationData.TranslationZ = 0.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Test, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    scene->addObject(light);
    scene->addLightSource(light);

    scene->addObject(sphere1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    return scene;
}
#pragma endregion

#pragma region object generation
DrawableObject* SceneGenerator::generateTree()
{
    //srand(static_cast<unsigned int>(time(0)));
    float randomScale = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.5f) + 0.5f;
    float randomRotation = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 360.0f);
    float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f;
    float randomZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 10.0f) - 5.0f; //TODO make generation only to 0.5f steps so that we have easier 
                                                                                              //work deleting trees from scene later down the road 

    return generateTree(randomScale, randomRotation, randomX, randomZ);
}

DrawableObject* SceneGenerator::generateTree(float scale, float rotation, float x, float z) {    
    std::string accessString = shaderProgramManager.CreateShaderNemec( "VertLight.shader", "FragLight.shader", "tree");
    ShaderProgram* shaderProgram = shaderProgramManager.getShader(accessString);
    DrawableObject* treeObject = new DrawableObject();
    treeObject->setShaderProgram(shaderProgram, accessString);


    treeObject->loadFromRawData(tree, 92814, 6);


    //TODO transformation order
    treeObject->scale(scale);
    treeObject->rotate(rotation, 0.0f, 1.0f, 0.0f);
    treeObject->translate(x, 0.0f, z);

    treeObject->updateTransformation();

    return treeObject;
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType) { //TODO since we need to use deep cloneing its 
                                                                                                                                            //much better to move this to contructor and use base class contructor
    DrawableObject* object = new DrawableObject();
    auto it = ShaderMappings.find(shaderType); //ShaderType handle
    ShaderProgram* shaderProgram = nullptr;    
    if (it == ShaderMappings.end()) {
        std::cerr << "Invalid ShaderType specified. Assigning default shader." << std::endl;
        it = ShaderMappings.find(ShaderType::Test);
    }
    ShaderInfo shaderInfo = it->second;
    std::string accessString = shaderProgramManager.CreateShaderNemec(shaderInfo.vertexPath.c_str(), shaderInfo.fragmentPath.c_str(), "generatedObject");
    shaderProgram = shaderProgramManager.getShader(accessString);
    if (shaderProgram) {
        object->setShaderProgram(shaderProgram);
    }
    auto modelIt = ModelMappings.find(modelType); //ModelType handle    
    if (modelIt != ModelMappings.end()) {
        const ModelData& modelData = modelIt->second;
        object->loadFromRawData(modelData.data, modelData.vertexCount, 6);
    }
    else {
        std::cerr << "Invalid ModelType specified. Assigning default model." << std::endl;
        const ModelData& modelData = ModelMappings.at(ModelType::PLAIN);
        object->loadFromRawData(modelData.data, modelData.vertexCount, 6);
    }
    object->scale(transformationData.Scale);
    object->rotate(transformationData.RotationAngle, transformationData.RotationX, transformationData.RotationY, transformationData.RotationZ);
    object->translate(transformationData.TranslationX, transformationData.TranslationY, transformationData.TranslationZ);
    object->updateTransformation();
    return object;
}
#pragma endregion

#pragma region light generation
LightSource* SceneGenerator::generateLightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, const glm::vec4& lightColor, float lightIntensity) {
    DrawableObject* baseObject = generateDrawableObject(transformationData, shaderType, modelType);
    LightSource* lightSource = new LightSource(*baseObject, lightColor, lightIntensity);
    delete baseObject;
    return lightSource;
}


#pragma endregion

