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
    MaterialProperties material(glm::vec3(0.5f), glm::vec3(0.7f), glm::vec3(0.8f));

    // Triangle 1
    DrawableObject* triangle = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::PLAIN_TEXTURE, glm::vec3(0.8f, 0.4f, 0.0f), material);

    glm::mat4 initialMatrix3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.0f, -2.0f));
    TransformationDynamicTranslateCube* dyntrans3 = new TransformationDynamicTranslateCube(0.5f, 0.8f, initialMatrix3,
        3.0f, 3.0f, 3.0f, -3.0f, -3.0f, -3.0f
    );
    TransformationDynamicTranslate* translatetransformation = new TransformationDynamicTranslate(initialMatrix3);

    triangle->transformationComposite.addTransformation(dyntrans3);
    triangle->transformationComposite.addTransformation(translatetransformation);

    scene->addObject(triangle);


    

    
    //DrawableObject* suzi = generateDrawableObject(ShaderType::Texture, "house.obj", new Texture("house.png"), material);

    //NewTransformationTranslate* translateTrans = new NewTransformationTranslate(glm::vec3(0.0f,0.0f,-2.0f));
    //NewTransformationDynamicRotate* rotateTrans = new NewTransformationDynamicRotate(glm::mat4(1.0f), glm::vec3(0.0f,1.0f,0.0f), 10.0f);
    //NewTransformationScale* scaleTrans = new NewTransformationScale(glm::vec3(0.05f));
    //
    //suzi->transformationComposite.addTransformation(translateTrans);
    //suzi->transformationComposite.addTransformation(rotateTrans);
    //suzi->transformationComposite.addTransformation(scaleTrans);
    //
    //
    //scene->getBehavioralManager()->addAnimeObject(rotateTrans);
    //
    //scene->addObject(suzi);

    // Light 1

    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);

    TransformationTranslate* translate = new TransformationTranslate(glm::vec3(1.0f, 1.0f, 1.0f));
    TransformationScale* lightScale = new TransformationScale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->transformationComposite.addTransformation(translate);
    light->transformationComposite.addTransformation(lightScale);


    std::vector<glm::vec3> bezpointvec = { glm::vec3(0.0f), glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(20.0f, 20.0f, 0.0f), glm::vec3(20.0f, 40.0f, 0.0f) };

    TransformationBezier* bezier = new TransformationBezier(glm::mat4(1.0f), bezpointvec, 1.0f);
    light->transformationComposite.addTransformation(bezier);
    
    scene->getBehavioralManager()->addAnimeObject(bezier);

    scene->addLightSource(light);


    //DirectionalLightSource* dirLight = new DirectionalLightSource(glm::vec3(0.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.4f);
    //scene->addLightSource(dirLight);

    //std::vector<std::string> faces = ;
    scene->addSkyBox({ "resources/posx.jpg", "resources/negx.jpg", "resources/posy.jpg", "resources/negy.jpg", "resources/posz.jpg", "resources/negz.jpg" });


    scene->setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
    scene->setCameraPosition(glm::vec3(0.0f, 5.0f, -5.0f));
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




    MaterialProperties materialProperties2(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(0.3f));
    DrawableObject* tree1 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, glm::vec3(0.8f, 0.4f, 0.0f), materialProperties2);
    scene->addObject(tree1);

    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::CUBE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light);
    //scene->addObject(tree);

    LightSource* light2 = generateLightSource(transformationData, ShaderType::Light, ModelType::CUBE, glm::vec4(1.0f), 1.0f);
    scene->addLightSource(light2);

    
    return scene;
}

Scene* SceneGenerator::generateForestScene(int numTrees, float areaSize, float minDistance) {
    Scene* forestScene = new Scene();



    

    // Ground using old TransformationData
    TransformationData groundTransformationData;

    MaterialProperties materialpropertiesforground(glm::vec3(0.2f), glm::vec3(0.55f), glm::vec3(0.002f), 1);

    Texture* grassTexture = new Texture("grass.png");

    DrawableObject* ground = generateDrawableObject(groundTransformationData, ShaderType::Texture_phong, ModelType::PLAIN_TEXTURE, glm::vec3(0.3f, 0.8f, 0.01f), materialpropertiesforground, grassTexture);

    // Add new transformations to ground
    TransformationScale* groundScale = new TransformationScale(glm::vec3(80.0f));
    TransformationRotate* groundRotate = new TransformationRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    ground->transformationComposite.addTransformation(groundScale);
    ground->transformationComposite.addTransformation(groundRotate);

    forestScene->addObject(ground);

    DrawableObject* house = generateDrawableObject(ShaderType::Texture_phong, "house.obj", new Texture("house.png"), materialpropertiesforground);
    TransformationTranslate* houseTranslate = new TransformationTranslate(glm::vec3(10.0f, 0.0f, 10.0f));
    TransformationScale* houseScale = new TransformationScale(glm::vec3(1.0f));
    house->transformationComposite.addTransformation(houseTranslate);
    house->transformationComposite.addTransformation(houseScale);

    forestScene->addObject(house);

    DrawableObject* suzi = generateDrawableObject(ShaderType::Texture, "login.obj", new Texture("grass.png"), materialpropertiesforground);
    //DrawableObject(ShaderType shaderType, char* modelFile, Texture* texture, MaterialProperties material);


    TransformationTranslate* translateTrans = new TransformationTranslate(glm::vec3(10.0f, 10.0f, 10.0f));
    TransformationDynamicRotate* rotateTrans = new TransformationDynamicRotate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 10.0f);
    TransformationTranslate* translateTrans2 = new TransformationTranslate(glm::vec3(-2.0f, 0.0f, 0.0f));
    TransformationScale* scaleTrans = new TransformationScale(glm::vec3(2.00f));

    suzi->transformationComposite.addTransformation(translateTrans);
    suzi->transformationComposite.addTransformation(rotateTrans);
    suzi->transformationComposite.addTransformation(translateTrans2);
    suzi->transformationComposite.addTransformation(scaleTrans);


    forestScene->getBehavioralManager()->addAnimeObject(rotateTrans);

    forestScene->addObject(suzi);


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

        // Tree using old TransformationData
        TransformationData treeTransformationData;

        float redTreeColor = 0.2f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.4f - 0.2f);
        float greenTreeColor = 0.4f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.9f - 0.4f);

        DrawableObject* tree = generateDrawableObject(treeTransformationData, ShaderType::Develop, ModelType::TREE, glm::vec3(redTreeColor, greenTreeColor, 0.0f));

        // Add new transformations to tree
        TransformationTranslate* treeTranslate = new TransformationTranslate(position);
        TransformationScale* treeScale = new TransformationScale(glm::vec3(1.0f));
        tree->transformationComposite.addTransformation(treeTranslate);
        tree->transformationComposite.addTransformation(treeScale);

        float randomChance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (randomChance <= 0.2f) {
            //TODO ROTATION AROUND POINT
            //tree->transformation.setDynamicAngle(60);
            //tree->transformation.setDynamicAxis(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        forestScene->addObject(tree);

        int numBushes = 10 + (rand() % 15);
        float calcdistance = minDistance * 10;

        for (int j = 0; j < numBushes; ++j) {
            float bushOffsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / calcdistance) - (calcdistance / 2);
            float bushOffsetZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / calcdistance) - (calcdistance / 2);

            glm::vec3 bushPosition = position + glm::vec3(bushOffsetX, 0.0f, bushOffsetZ);

            // Bush using old TransformationData
            TransformationData bushTransformationData;

            float redBushColor = 0.2f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.4f - 0.2f);
            float greenBushColor = 0.4f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.9f - 0.4f);

            DrawableObject* bush = generateDrawableObject(bushTransformationData, ShaderType::Develop, ModelType::BUSH, glm::vec3(redBushColor, greenBushColor,0.0f));


            float bushScalef = 1.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (2.9f - 1.0f);
            // Add new transformations to bush
            TransformationTranslate* bushTranslate = new TransformationTranslate(bushPosition);
            TransformationScale* bushScale = new TransformationScale(glm::vec3(bushScalef));
            bush->transformationComposite.addTransformation(bushTranslate);
            bush->transformationComposite.addTransformation(bushScale);

            forestScene->addObject(bush);
        }
    }
    forestScene->setCameraDirection(glm::vec3(0.0f, -0.2f, 1.0f));
    forestScene->setCameraPosition(glm::vec3(0.0f, 5.0f, -2.0f));

    generateWhisps(forestScene, 4);

    

    return forestScene;
}

//TODO make it so that my eyes does not bleed blood
Scene* SceneGenerator::generateNightForestScene(int numTrees, float areaSize, float minDistance) {
    Scene* forestScene = new Scene();


    forestScene->addSkyBox({ "resources/posx.jpg", "resources/negx.jpg", "resources/posy.jpg", "resources/negy.jpg", "resources/posz.jpg", "resources/negz.jpg" });

    // Ground using old TransformationData
    TransformationData groundTransformationData;

    MaterialProperties materialpropertiesforground(glm::vec3(0.2f), glm::vec3(0.55f), glm::vec3(0.002f), 1);

    DrawableObject* ground = generateDrawableObject(groundTransformationData, ShaderType::Develop, ModelType::PLAIN, glm::vec3(0.3f, 0.8f, 0.01f), materialpropertiesforground);

    // Add new transformations to ground
    TransformationScale* groundScale = new TransformationScale(glm::vec3(80.0f));
    TransformationRotate* groundRotate = new TransformationRotate(90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    ground->transformationComposite.addTransformation(groundScale);
    ground->transformationComposite.addTransformation(groundRotate);

    forestScene->addObject(ground);

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

        // Tree using old TransformationData
        TransformationData treeTransformationData;

        float redTreeColor = 0.2f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.4f - 0.2f);
        float greenTreeColor = 0.4f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (0.9f - 0.4f);

        DrawableObject* tree = generateDrawableObject(treeTransformationData, ShaderType::Develop, ModelType::TREE, glm::vec3(redTreeColor, greenTreeColor, 0.0f));

        // Add new transformations to tree
        TransformationTranslate* treeTranslate = new TransformationTranslate(position);
        TransformationScale* treeScale = new TransformationScale(glm::vec3(1.0f));
        tree->transformationComposite.addTransformation(treeTranslate);
        tree->transformationComposite.addTransformation(treeScale);

        float randomChance = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (randomChance <= 0.2f) {
            //TODO ROTATION AROUND POINT
            //tree->transformation.setDynamicAngle(60);
            //tree->transformation.setDynamicAxis(glm::vec3(0.0f, 1.0f, 0.0f));
        }

        forestScene->addObject(tree);

        int numBushes = 5 + (rand() % 15);
        float calcdistance = minDistance * 10;

        //for (int j = 0; j < numBushes; ++j) {
        //    float bushOffsetX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / calcdistance) - (calcdistance / 2);
        //    float bushOffsetZ = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / calcdistance) - (calcdistance / 2);

        //    glm::vec3 bushPosition = position + glm::vec3(bushOffsetX, 0.0f, bushOffsetZ);

        //    // Bush using old TransformationData
        //    TransformationData bushTransformationData;

        //    DrawableObject* bush = generateDrawableObject(bushTransformationData, ShaderType::Test, ModelType::BUSH);

        //    // Add new transformations to bush
        //    NewTransformationTranslate* bushTranslate = new NewTransformationTranslate(bushPosition);
        //    NewTransformationScale* bushScale = new NewTransformationScale(glm::vec3(0.5f));
        //    bush->transformationComposite.addTransformation(bushTranslate);
        //    bush->transformationComposite.addTransformation(bushScale);

        //    forestScene->addObject(bush);
        //}
    }

    DirectionalLightSource* dirLight = new DirectionalLightSource(glm::vec3(0.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.4f);
    forestScene->addLightSource(dirLight);



    //forestScene->addLightSource(dirLight);

    forestScene->setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
    forestScene->setCameraPosition(glm::vec3(0.0f, 4.0f, -2.0f));

    return forestScene;
}






Scene* SceneGenerator::generateSphereScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;
    glm::vec3 color = glm::vec3(0.8f, 0.4f, 0.1f);
    MaterialProperties material(glm::vec3(0.05f), glm::vec3(0.9f), glm::vec3(0.95f), 64);
    MaterialProperties material2(glm::vec3(0.1f), glm::vec3(0.35f), glm::vec3(0.2f), 4);
    MaterialProperties material3(glm::vec3(0.1f), glm::vec3(0.6f), glm::vec3(0.001f), 1);
    MaterialProperties material4(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(0.7f), 32);


    DrawableObject* sphere1 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, color, material);
    sphere1->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(1.5f, 1.5f, 0.0f)));

    DrawableObject* sphere2 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, color, material2);
    sphere2->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(-1.5f, 1.5f, 0.0f)));

    DrawableObject* sphere3 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, color, material3);
    sphere3->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(1.5f, -1.5f, 0.0f)));

    DrawableObject* sphere4 = generateDrawableObject(transformationData, ShaderType::Develop, ModelType::SPHERE, color, material4);
    sphere4->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(-1.5f, -1.5f, 0.0f)));

    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    light->transformationComposite.addTransformation(new TransformationScale(glm::vec3(0.1f)));
    

    scene->addObject(sphere1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addLightSource(light);

    scene->setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
    scene->setCameraPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    return scene;
}


Scene* SceneGenerator::generateShadersSphereScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;

    DrawableObject* sphere1 = generateDrawableObject(transformationData, ShaderType::CONSTANT, ModelType::SPHERE);
    sphere1->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(1.5f, 1.5f, 0.0f)));

    DrawableObject* sphere2 = generateDrawableObject(transformationData, ShaderType::Blinn, ModelType::SPHERE);
    sphere2->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(-1.5f, 1.5f, 0.0f)));

    DrawableObject* sphere3 = generateDrawableObject(transformationData, ShaderType::Phong, ModelType::SPHERE);
    sphere3->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(1.5f, -1.5f, 0.0f)));

    DrawableObject* sphere4 = generateDrawableObject(transformationData, ShaderType::Lambert, ModelType::SPHERE);
    sphere4->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(-1.5f, -1.5f, 0.0f)));

    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    light->transformationComposite.addTransformation(new TransformationScale(glm::vec3(0.1f)));


    scene->addObject(sphere1);
    scene->addObject(sphere2);
    scene->addObject(sphere3);
    scene->addObject(sphere4);
    scene->addLightSource(light);

    scene->setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
    scene->setCameraPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    return scene;
}

Scene* SceneGenerator::generateTextureScene() {
    Scene* scene = new Scene();
    TransformationData transformationData;
    MaterialProperties material(glm::vec3(0.5f), glm::vec3(0.7f), glm::vec3(0.8f));

    Texture* texture = new Texture("test.png");
    Texture* texture2 = new Texture("grass.png");

    TransformationDynamicRotate* rotateTrans = new TransformationDynamicRotate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
    TransformationRotate* rotateDTrans = new TransformationRotate(90.0f, glm::vec3(1.0f,0.0f,0.0f));


    DrawableObject* texturePlain1 = generateDrawableObject(transformationData, ShaderType::Texture, ModelType::PLAIN_TEXTURE, glm::vec3(0.0,0.0,0.0), material, texture);
    texturePlain1->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(1.5f, 1.5f, 0.0f)));
    texturePlain1->transformationComposite.addTransformation(rotateDTrans);
    texturePlain1->transformationComposite.addTransformation(rotateTrans);

    DrawableObject* texturePlain2 = generateDrawableObject(transformationData, ShaderType::Texture, ModelType::PLAIN_TEXTURE, glm::vec3(0.0, 0.0, 0.0), material, texture2);
    texturePlain2->transformationComposite.addTransformation(new TransformationTranslate(glm::vec3(-1.5f, 1.5f, 0.0f)));
    texturePlain2->transformationComposite.addTransformation(rotateDTrans);
    texturePlain2->transformationComposite.addTransformation(rotateTrans);


    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, glm::vec4(1.0f), 1.0f);
    light->transformationComposite.addTransformation(new TransformationScale(glm::vec3(0.1f)));


    scene->getBehavioralManager()->addAnimeObject(rotateTrans);


    scene->addObject(texturePlain1);
    scene->addObject(texturePlain2);

    scene->addLightSource(light);

    scene->setCameraDirection(glm::vec3(0.0f, 0.0f, 1.0f));
    scene->setCameraPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    return scene;
}



#pragma endregion

#pragma region object generation

LightSource* SceneGenerator::generateWhisp(Scene* scene, WhispData whispData) {
    TransformationData transformationData; //this is deprecated but yet its necesary to be there will be removed after cleanup
    LightSource* light = generateLightSource(transformationData, ShaderType::Light, ModelType::SPHERE, whispData.lightData.color, 1.0f);

    glm::mat4 initialMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(whispData.transformationData.TranslationX, whispData.transformationData.TranslationY, whispData.transformationData.TranslationZ));
    TransformationDynamicTranslateCube* dyntrans = new TransformationDynamicTranslateCube(whispData.dynamicTranslateCubeData);

    TransformationScale* lightScale = new TransformationScale(glm::vec3(whispData.transformationData.Scale));
    light->transformationComposite.addTransformation(dyntrans);
    light->transformationComposite.addTransformation(lightScale);

    scene->getBehavioralManager()->addAnimeObject(dyntrans);
    scene->addLightSource(light);

    return light;
}

vector<LightSource*> SceneGenerator::generateWhisps(Scene* scene, int count) {
    vector<LightSource*> whisps;

    for (int i = 0; i < count; ++i) {
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 60.0f) - 30.0f;
        float y = 2.0f;  
        float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 60.0f) - 30.0f;

        // TransformationData setup
        TransformationData transformationData;
        transformationData.Scale = 0.1f;
        transformationData.TranslationX = x;
        transformationData.TranslationY = y;
        transformationData.TranslationZ = z;


        float maxHeight = 10.0f;  
        float minHeight = 0.0f;   

        float maxWidth = x + 10.0f;  
        float minWidth = x - 10.0f;  

        float maxLength = z + 10.0f;  
        float minLength = z - 10.0f;  

        DynamicTranslateCubeData dynamicTranslateCubeData(
            2.0f,  
            2.0f,  
            glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)), // Initial Matrix
            maxHeight, maxWidth, maxLength,
            minHeight, minWidth, minLength
        );

        LightData lightData(glm::vec4(1.0f), glm::vec3(x, y, z));

        WhispData whispData(transformationData, dynamicTranslateCubeData, lightData);

        LightSource* whisp = generateWhisp(scene, whispData);
        whisps.push_back(whisp);
    }

    return whisps;
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, MaterialProperties material, Texture* texture) {
    return new DrawableObject(transformationData, shaderType, modelType, color, material, texture);
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color, MaterialProperties material) {
    return new DrawableObject(transformationData, shaderType, modelType, color, material);
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType, glm::vec3 color) {
    return new DrawableObject(transformationData, shaderType, modelType, color);
}

DrawableObject* SceneGenerator::generateDrawableObject(TransformationData transformationData, ShaderType shaderType, ModelType modelType) {
    return new DrawableObject(transformationData, shaderType, modelType); 
}

DrawableObject* SceneGenerator::generateDrawableObject(ShaderType shaderType,const char* modelFile, Texture* texture, MaterialProperties material) {
    return new DrawableObject(shaderType, modelFile, texture, material);
}
#pragma endregion

#pragma region light generation
LightSource* SceneGenerator::generateLightSource(TransformationData transformationData, ShaderType shaderType, ModelType modelType, const glm::vec4& lightColor, float lightIntensity) {
    glm::vec3 colorCopy = glm::vec3(lightColor);  // Convert glm::vec4 to glm::vec3 by copying RGB values
    LightSource* lightSource = new LightSource(transformationData, shaderType, modelType, colorCopy, lightColor, lightIntensity);
    return lightSource;
}


#pragma endregion

