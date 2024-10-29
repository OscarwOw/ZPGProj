#include "SceneManager.h"

//SceneManager::SceneManager() : currentSceneIndex(0) {}

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::addScene(const std::string& name, Scene* scene) {
	scenes[name] = scene;
}

void SceneManager::switchScene(const std::string& name) {
	if (scenes.find(name) != scenes.end()) {
		currentSceneName = name;
	}
}

Scene* SceneManager::getCurrentScene() {
	auto it = scenes.find(currentSceneName);
	if (it != scenes.end()) {
		return it->second;
	}
	return nullptr;
}
