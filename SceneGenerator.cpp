#pragma once
#include "SceneGenerator.h"




SceneGenerator& SceneGenerator::getInstance()
{
    static SceneGenerator instance;
    return instance;
}


#pragma region scene generation functions 
Scene* SceneGenerator::generateTraingleScene() {
    Scene* scene = new Scene(); 
    TransformationData transformationData;
    DrawableObject* triangle = generateTriangle(transformationData);
    scene->addObject(triangle);
    return scene;
}

Scene* SceneGenerator::generateTestTreeScene()
{
    Scene* scene = new Scene();
    TransformationData transformationData;
    //DrawableObject* tree = generateTree();
    DrawableObject* tree = generateDrawableObject(transformationData, ShaderType::Test, ModelType::TREE);

    scene->addObject(tree);
    return scene;
}

Scene* SceneGenerator::generateForestScene(int numTrees, int numBushes)
{
    Scene* scene = new Scene();

    for (int i = 0; i < numTrees; i++) {
        DrawableObject* treeobject = generateTree();
        scene->addObject(treeobject);
    }
    return scene;
}

Scene* SceneGenerator::generateSphereScene() {
    Scene* scene = new Scene();
    return scene;
}
#pragma endregion

DrawableObject* SceneGenerator::generateTriangle(TransformationData transformationData) {
    std::string accessString = shaderProgramManager.CreateShaderNemec("VertLight.shader", "FragLight.shader", "plain");
    ShaderProgram* shaderProgram = shaderProgramManager.getShader(accessString);
    DrawableObject* triangle = new DrawableObject();
    triangle->setShaderProgram(shaderProgram, accessString);
    triangle->loadFromRawData(plain, 36, 6);
    triangle->scale(transformationData.Scale);
    triangle->rotate(transformationData.RotationAngle, transformationData.RotationX, transformationData.RotationY, transformationData.RotationZ);
    triangle->translate(transformationData.TranslationX, transformationData.TranslationY, transformationData.TranslationZ);
    triangle->updateTransformation();
    //Camera::getInstance().attachObserver(shaderProgram);
    return triangle;
}


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

DrawableObject* SceneGenerator::generateSphere(TransformationData transformationData)
{
    std::string accessString = shaderProgramManager.CreateShaderNemec("VertLight.shader", "FragLight.shader", "tree");
    ShaderProgram* shaderProgram = shaderProgramManager.getShader(accessString);
    DrawableObject* sphereObject = new DrawableObject();
    sphereObject->setShaderProgram(shaderProgram, accessString);

    sphereObject->loadFromRawData(sphere, 17280, 6);

    return sphereObject;
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType) {
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


void SceneGenerator::loadAndAttachTreeShader(DrawableObject* treeObject) { //posibly deprecated
    if (shaderProgramManager.getShader("treeShader") == nullptr) {
        shaderProgramManager.CreateShader("treeShader", "tree.h");
    }

    ShaderProgram* shader = shaderProgramManager.getShader("treeShader");
    if (shader) {
        treeObject->setShaderProgram(shader);
    }
}



DrawableObject* SceneGenerator::generateBush()
{
    return nullptr;
}

