#include "SceneManager.h"

//SceneManager::SceneManager() : currentSceneIndex(0) {}

SceneManager& SceneManager::getInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::addScene(Scene* scene)
{
	scenes.push_back(scene);
}

void SceneManager::switchScene(int index)
{
	if (index >= 0 && index < scenes.size()) {
		currentSceneIndex = index;
	}
}

Scene* SceneManager::getCurrentScene()
{
	if (currentSceneIndex >= 0 && currentSceneIndex < scenes.size()) {
		return scenes.at(currentSceneIndex);
	}
	return nullptr;
}
