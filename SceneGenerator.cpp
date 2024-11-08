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
    DrawableObject* triangle = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::TRIANGLE, glm::vec3(0.8f, 0.4f, 0.0f));
    scene->addObject(triangle);


    transformationData.TranslationX = -2.0f;
    transformationData.TranslationY = 2.0f;
    transformationData.TranslationZ = 0.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light);
    
    //scene->addLightSource(light);

    return scene;
}

Scene* SceneGenerator::generateTestTreeScene()
{
    Scene* scene = new Scene();
    TransformationData transformationData;
    transformationData.TranslationX = -1.0f;
    MaterialProperties materialProperties(glm::vec3(0.08f), glm::vec3(0.2f), glm::vec3(1.0f));
    
    DrawableObject* tree = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, glm::vec3(0.8f, 0.4f, 0.0f), materialProperties);
    scene->addObject(tree);



    transformationData.TranslationX = 1.0f;
    transformationData.TranslationY = 0.0f;
    transformationData.TranslationZ = 0.0f;
    MaterialProperties materialProperties2(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(0.3f));
    DrawableObject* tree1 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, glm::vec3(0.8f, 0.4f, 0.0f), materialProperties2);
    scene->addObject(tree1);

    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 2.0f;
    transformationData.TranslationZ = 2.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::CUBE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light);
    //scene->addObject(tree);

    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 2.0f;
    transformationData.TranslationZ = -2.0f;
    transformationData.Scale = 0.1f;
    LightSource* light2 = generateLightSource(transformationData, ShaderType::Light, ModelType::CUBE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light2);


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

        DrawableObject* tree = generateDrawableObject(treeTransformationData, ShaderType::Phong, ModelType::TREE);

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
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    forestScene->addLightSource(light);
    forestScene->addObject(light);
    return forestScene;
}


Scene* SceneGenerator::generateSphereScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;
    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere1 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere2 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);

    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere3 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere4 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);

    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 0.0f;
    transformationData.TranslationZ = 0.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    //scene->addObject(light);
    

    scene->addObject(sphere1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addLightSource(light);
    return scene;
}


Scene* SceneGenerator::generateShadersSphereScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;
    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere1 = generateDrawableObject(transformationData, ShaderType::CONSTANT, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = 1.5f;
    DrawableObject* sphere2 = generateDrawableObject(transformationData, ShaderType::Blinn, ModelType::SPHERE);

    transformationData.TranslationX = 1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere3 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);

    transformationData.TranslationX = -1.5f;
    transformationData.TranslationY = -1.5f;
    DrawableObject* sphere4 = generateDrawableObject(transformationData, ShaderType::Lambert, ModelType::SPHERE);

    transformationData.TranslationX = 0.0f;
    transformationData.TranslationY = 0.0f;
    transformationData.TranslationZ = 0.0f;
    transformationData.Scale = 0.1f;
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
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



DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, MaterialProperties material) {
    return new DrawableObject(transformationData, shaderType, modelType, color, material);
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color) {
    return new DrawableObject(transformationData, shaderType, modelType, color);
}

//DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color) { //TODO since we need to use deep cloneing its 
//                                                                                                                                                             //much better to move this to contructor and use base class contructor
//    DrawableObject* object = generateDrawableObject(transformationData, shaderType, modelType);
//    object->setColor(color);
//    return object;
//}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType) {
    return new DrawableObject(transformationData, shaderType, modelType); 
}
#pragma endregion

#pragma region light generation
LightSource* SceneGenerator::generateLightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, const glm::vec4& lightColor, float lightIntensity) {
    glm::vec3 colorCopy = glm::vec3(lightColor);  // Convert glm::vec4 to glm::vec3 by copying RGB values
    LightSource* lightSource = new LightSource(transformationData, shaderType, modelType, colorCopy, lightColor, lightIntensity);
    return lightSource;
}


#pragma endregion

