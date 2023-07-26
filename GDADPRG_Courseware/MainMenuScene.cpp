#include "MainMenuScene.h"
#include "MainMenuScreen.h"
#include "GameObjectManager.h"
#include <iostream>

MainMenuScene::MainMenuScene() : AScene("MainMenuScene")
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onLoadResources()
{

}

void MainMenuScene::onLoadObjects()
{
	MainMenuScreen* menuScreen = new MainMenuScreen("MainMenuScreen");
	this->registerObject(menuScreen);
}

void MainMenuScene::onUnloadResources()
{

}