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
	Scene* scene = SceneGenerator::getInstance().generateTraingleScene();
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
	Scene* scene = SceneGenerator::getInstance().generateForestScene(50, 50);
	addScene(name, scene);
	return scene;
}


void SceneManager::switchScene(const std::string& name) { //optimized switch scene
	auto scene = scenes.find(name);

	if (scene != scenes.end()) {
		std::vector<DrawableObject*> newObjects = scene->second->getObjects();

		Scene* currentscene = getCurrentScene();
		if (currentscene == nullptr) {
			for (DrawableObject* obj : newObjects) {
				Camera::getInstance().attachObserver(obj->getSaherProgram());
			}
			currentSceneName = name;
			return;
		}

		std::vector<DrawableObject*> objects = getCurrentScene()->getObjects();
		for (int i=0; i<objects.size(); i++)
		{			
			Camera::getInstance().detachObserver(objects[i]->getSaherProgram());
		}
		
		
		for (DrawableObject* obj : newObjects) {
			Camera::getInstance().attachObserver(obj->getSaherProgram());
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
