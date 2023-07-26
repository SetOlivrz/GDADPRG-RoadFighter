#include "MainMenuScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "UIButton.h"
#include "UIText.h"
#include "SamplePopupScreen.h"
#include "GameObjectManager.h"
#include <iostream>
#include "SceneManager.h"
#include "QuitScreen.h"
#include "ARendererFactory.h"
#include "RendererFactory.h"


MainMenuScreen::MainMenuScreen(string name) : AGameObject(name), ButtonListener()
{
}

MainMenuScreen::~MainMenuScreen()
{
	AGameObject::~AGameObject();
}

void MainMenuScreen::initialize()
{
	
	// assign texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	Renderer* renderer = factory->createSprite("title_bg", "spritesheet", "title_bg", sprite);
	this->attachComponent(renderer);

	//set position
	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	//button state textures
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	//start game button
	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setPosition(-100, 300);
	button1->getTransformable()->setScale(0.3f, 0.3f); 
	button1->setButtonListener(this);
	
	UIText* button_1Text = new UIText("text_1");
	button1->attachChild(button_1Text);
	button_1Text->setPosition(0, 10);
	button_1Text->setSize(75);
	button_1Text->setText("START");
	
	
	//exit button
	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setPosition(100, 300);
	button2->getTransformable()->setScale(0.3f, 0.3f);
	button2->setButtonListener(this);
	UIText* button_2Text = new UIText("text_1");
	button2->attachChild(button_2Text);
	button_2Text->setPosition(0, 10);
	button_2Text->setSize(75);
	button_2Text->setText("EXIT");
}

void MainMenuScreen::onButtonClick(UIButton* button)
{
}

void MainMenuScreen::onButtonReleased(UIButton* button)
{
	// load game scene 1 if button 1 , else displayer quit screen
	if (button->getName() == "button_1") {
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_NAME);
	}
	else if (button->getName() == "button_2") {
		QuitScreen* quitScreen = new QuitScreen("QuitScreen");
		quitScreen->markMainMenuQuit();
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}


