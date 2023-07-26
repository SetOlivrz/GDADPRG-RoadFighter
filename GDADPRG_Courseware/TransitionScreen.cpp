#include "TransitionScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "PhysicsManager.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "ScoreManager.h"
#include "UIText.h"

TransitionScreen::TransitionScreen(string name, int level): AGameObject(name, level),ButtonListener()
{
}

TransitionScreen::~TransitionScreen()
{

}

void TransitionScreen::initialize()
{
	
	//score text
	UIText* score = new UIText("text_5");
	//do not make as a button child. difficult to position
	this->attachChild(score);
	score->setPosition(Game::WINDOW_WIDTH/2, Game::WINDOW_HEIGHT/2-100);
	score->setSize(35);
	score->setColorOutThickness(7);
	score->setText(to_string(ScoreManager::getInstance()->getScore()));

	// main window
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	sf::Vector2f center = sf::Vector2f(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	//restart button
	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(center.x-150, center.y+50);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(0, 0);
	button_1Text->setSize(50);
	button_1Text->setText("RESTART");

	//next level button
	button = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(center.x+150, center.y+50);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button->attachChild(button_2Text);
	button_2Text->setPosition(0, 0);
	button_2Text->setSize(50);
	button_2Text->setText("NEXT");
}

void TransitionScreen::onButtonClick(UIButton* button)
{
}

void TransitionScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1") // restart level
	{
		
		SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_NAME);
		ScoreManager::getInstance()->destroy();
	}
	else if (button->getName() == "button_2")  // next level
	{
		switch(level)
		{
			case 1: SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_2_NAME); break;
			case 2: SceneManager::getInstance()->loadScene(SceneManager::GAME_SCENE_3_NAME); break;
			case 3: SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME); break;
		}
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}
