#include "Scene.h"

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
    addLightObserver(object->getSaherProgram());
}

void Scene::drawScene(float time) {
    if (_hasSkyBox) {
        drawSkybox();
    }
    _behavioralManager->update(time);
    publishLights();

    for (auto& object : objects) {
        object->Draw(); 
    }
}

void Scene::clearScene() {
    for (auto& object : objects) {
        delete object;  
    }
    objects.clear(); 
}

void Scene::addLightObserver(ILightObserver* observer)
{
    _lightPublisher.attachObserver(observer);
    publishLights();
}

void Scene::publishLights()
{
    _lightPublisher.publish();
}

void Scene::addLightSource(ILightEmitter* lightEmitter) {
    LightSource* lightSource = dynamic_cast<LightSource*>(lightEmitter);
    if (lightSource != nullptr) {
        // If dynamic_cast is successful, add it to the scene as a drawable object
        addObject(lightSource);
    }
    _lightPublisher.attachLightSource(lightEmitter);
    _hasLightSource = true;
    publishLights();
}

void Scene::addSkyBox(std::vector<std::string> faces) {
    glGenBuffers(1, &_skyboxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skycube), &skycube, GL_STATIC_DRAW);


    glGenVertexArrays(1, &_skyboxVAO);
    glBindVertexArray(_skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);


    _skyboxTexture = new Texture(faces);
    _hasSkyBox = true;

    std::string shaderstring = ShaderProgramManager::getInstance().CreateShaderNemec("vert_cube_map.shader", "frag_cube_map.shader", "cubemap");
    _skyboxShaderProgram = ShaderProgramManager::getInstance().getShader(shaderstring);


    


    //glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture->getTextureID());
    //glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    //_skyboxShaderProgram->use();
    //GLint idTexUnit = glGetUniformLocation(_skyboxShaderProgram->getProgramID(), "skybox");
    //glUniform1i(idTexUnit, 0);

    /*Camera::getInstance().attachObserver(_skyboxShaderProgram);*/

    /*ShaderProgramManager::getInstance().CreateShaderNemec()*/
}
void Scene::drawSkybox() {
    glDepthFunc(GL_LEQUAL);
    //glDepthMask(GL_FALSE);

    // Bind the skybox shader
    glUseProgram(_skyboxShaderProgram->getProgramID());
    glm::mat4 pojection = Camera::getInstance().getPerspectiveMatrix();
    glm::mat4 view = Camera::getInstance().getViewMatrix();
    view = glm::mat4(glm::mat3(view));
    glUniform1i(glGetUniformLocation(_skyboxShaderProgram->getProgramID(), "skybox"), 0);
    glUniformMatrix4fv(glGetUniformLocation(_skyboxShaderProgram->getProgramID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(_skyboxShaderProgram->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(pojection));

    glBindVertexArray(_skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture->getTextureID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);


    
}

//std::vector<LightSource*> Scene::getLightSources() {
//    return _lightSources;
//}
bool Scene::hasLightSource() {
    return _hasLightSource;
}



void Scene::circusTransform()//deprecated
{
    TransformationData transformationdata = objects[0]->GetCurrentTransformationData();

    //objects[0]->getSaherProgram()->updatePerspective();


    //if (transformationdata.RotationAngle < 360) {//(transformationdata.RotationAngle < 360.0f) {
    //    objects[0]->rotate(transformationdata.RotationAngle + 5.0f, transformationdata.RotationX,
    //                       transformationdata.RotationY, transformationdata.RotationZ);
    //    //objects[0]->translate(transformationdata.TranslationX + 0.005f, transformationdata.TranslationY , transformationdata.TranslationZ );
    //    //objects[0]->scale(0.3f );
    //}
    //else {
    //    objects[0]->rotate(0, transformationdata.RotationX,
    //                       transformationdata.RotationY, transformationdata.RotationZ);
    //    /*objects[0]->translate( 0, transformationdata.TranslationY, transformationdata.TranslationZ);*/

    //}

}


std::vector<DrawableObject*> Scene::getObjects()
{
    return objects;
}

BehaviorManager* Scene::getBehavioralManager()
{
    return _behavioralManager;
}

void Scene::setBehavioralManager(BehaviorManager* behaviorManager)
{
    _behavioralManager = behaviorManager;
}

void Scene::setCameraDirection(glm::vec3 direction)
{
    _cameraDirection = direction;
}

void Scene::setCameraPosition(glm::vec3 position)
{
    _cameraPosition = position;
}

glm::vec3 Scene::getCameraDirection()
{
    return _cameraDirection;
}

glm::vec3 Scene::getCameraPosition()
{
    return _cameraPosition;
}
