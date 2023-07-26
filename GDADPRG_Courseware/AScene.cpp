#include "AScene.h"
#include "GameObjectManager.h"
#include "AudioManager.h"

AScene::AScene(string sceneName)
{
	this->sceneName = sceneName;
}

AScene::~AScene()
{

}

void AScene::onUnloadObjects()
{
	GameObjectManager::getInstance()->deleteAllObjectsInScene();
	AudioManager::getInstance()->stopAllSounds();
}

string AScene::getSceneName()
{
	return this->sceneName;
}

void AScene::registerObject(AGameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}