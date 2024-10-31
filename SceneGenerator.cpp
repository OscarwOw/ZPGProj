#include "SceneGenerator.h"
#include <cstdlib>
#include <ctime> 
#include "tree.h"

SceneGenerator& SceneGenerator::getInstance()
{
    static SceneGenerator instance;
    return instance;
}

void SceneGenerator::generateForest(Scene* scene, int numTrees, int numBushes, Camera* camera) //TODO rework camera
{
    DrawableObject* treeobject;

    for (int i = 0; i < numTrees; i++) {
        treeobject = generateTree();
        scene->addObject(treeobject);
        //camera->attachObserver(treeobject->getSaherProgram());
        glm::mat4 camera(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 10.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
        treeobject->getSaherProgram()->setViewMatrix(camera);
    }
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
    std::string accessString = shaderProgramManager.CreateShaderNemec( "ColorVertexShader.shader", "ColorFragmentShader.shader", "tree");
    //std::string accessString = shaderProgramManager.CreateShaderNemec( "VertexShaderFirstLight.shader", "FragmentShaderFirstLight.shader", "tree");
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

