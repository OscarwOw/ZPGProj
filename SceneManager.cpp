#include "SceneManager.h" 


SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::addScene(const std::string& name, Scene* scene) {
	scenes[name] = scene;
}

Scene* SceneManager::generateTraingleScene(std::string name) {
	Scene* scene = SceneGenerator::getInstance().generateDefaultScene();
	addScene(name, scene);
	return scene;
}

Scene* SceneManager::generateTestTreeScene(std::string name)
{
	Scene* scene = SceneGenerator::getInstance().generateTestTreeScene();
	addScene(name, scene);
	return scene;
}

Scene* SceneManager::generateForestScene(std::string name) {
	Scene* scene = SceneGenerator::getInstance().generateForestScene(50, 100.0f, 1.5f);		//.generateForestScene(50, 50);
	addScene(name, scene);
	return scene;
}

Scene* SceneManager::generateSphereScene(std::string name) {
	Scene* scene = SceneGenerator::getInstance().generateSphereScene();
	addScene(name, scene);
	return scene;
}

void SceneManager::switchScene(const std::string& name) { //TODO debug shows that current scene is not properly cleared!!! objects from current scene display newscene objects for no reason
	auto scene = scenes.find(name);

	if (scene != scenes.end()) {
		std::vector<DrawableObject*> newObjects = scene->second->getObjects();

		Scene* currentscene = getCurrentScene();
		if (currentscene == nullptr) {
			for (DrawableObject* object : newObjects) {
				Camera::getInstance().attachObserver(object->getSaherProgram());
			}
			currentSceneName = name;
			return;
		}

		std::vector<DrawableObject*> objects = getCurrentScene()->getObjects();

		for (int i=0; i<objects.size(); i++)
		{			
			Camera::getInstance().detachObserver(objects[i]->getSaherProgram());
		}
		
		if (scene->second->hasLightSource()) { //wierd looking strcture but its optimized 
			LightSource* lightSource = scene->second->getLightSource();
			std::vector<ILightObserver*> lightObservers = lightSource->getObservers();
			for (ILightObserver* object : lightObservers) {
				lightSource->detachObserver(object);
			}
			for (DrawableObject* object : newObjects) {
				Camera::getInstance().attachObserver(object->getSaherProgram());
				lightSource->attachObserver(object->getSaherProgram());
			}
		}
		else {
			for (DrawableObject* object : newObjects) {
				Camera::getInstance().attachObserver(object->getSaherProgram());
			}
		}		
		currentSceneName = name;
	}
}



void SceneManager::switchToNextScene() {
	switchScene(getNextScene());
}


std::string SceneManager::getNextScene() {
	auto it = scenes.find(currentSceneName);
	if (it != scenes.end()) {
		++it;
		if (it == scenes.end()) {
			it = scenes.begin();
		}
		currentSceneName = it->first;
		return it->first;
	}
	return nullptr;
}


Scene* SceneManager::getCurrentScene() {
	auto it = scenes.find(currentSceneName);
	if (it != scenes.end()) {
		return it->second;
	}
	return nullptr;
}
