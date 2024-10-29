#include "Scene.h"

void Scene::addObject(DrawableObject* obj) {
    objects.push_back(obj);
}

void Scene::drawScene() {
    for (auto& obj : objects) {
        obj->Draw(); 
    }
}

void Scene::clearScene() {
    for (auto& obj : objects) {
        delete obj;  
    }
    objects.clear(); 
}

void Scene::circusTransform()
{
    TransformationData transformationdata = objects[0]->GetCurrentTransformationData();

    //objects[0]->getSaherProgram()->updatePerspective();


    if (transformationdata.RotationAngle < 360) {//(transformationdata.RotationAngle < 360.0f) {
        objects[0]->rotate(transformationdata.RotationAngle + 5.0f, transformationdata.RotationX,
                           transformationdata.RotationY, transformationdata.RotationZ);
        //objects[0]->translate(transformationdata.TranslationX + 0.005f, transformationdata.TranslationY , transformationdata.TranslationZ );
        //objects[0]->scale(0.3f );
    }
    else {
        objects[0]->rotate(0, transformationdata.RotationX,
                           transformationdata.RotationY, transformationdata.RotationZ);
        /*objects[0]->translate( 0, transformationdata.TranslationY, transformationdata.TranslationZ);*/

    }

}
