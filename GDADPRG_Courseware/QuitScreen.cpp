#include "QuitScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "ScoreManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "AudioManager.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "AudioManager.h"

QuitScreen::QuitScreen(string name) : AGameObject(name), ButtonListener()
{
}

QuitScreen::~QuitScreen()
{
	AGameObject::~AGameObject();
}

void QuitScreen::initialize()
{
	//black screen texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	Renderer* renderer = factory->createSprite("UIBGRenderer", "texture","black_bg", sprite);
	this->attachComponent(renderer);
	sprite->setScale(3, 3);

	//setting position
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	//pressed and unpressed button texture
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");
	
	//YES button
	UIButton* button = new UIButton("yes", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(-150,  100);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(0, 0);
	button_1Text->setSize(60);
	button_1Text->setText("YES");

	
	//if lose screen instance
	if(this->name == "lose_screen")
	{
		//score text
		UIText* score_text = new UIText("score_text");
		this->attachChild(score_text);
		score_text->setPosition(-75, -100);
		score_text->setText(" GAME OVER\n    Score: " + to_string(ScoreManager::getInstance()->getScore()));	//game over lose text
		score_text->setSize(50);

		//change YES button to BACK button
		button->setPosition(0, 100);
		button_1Text->setText("BACK");
	}
	//if end screen instance
	else if(this->name == "end_screen")
	{
		//score text
		UIText* score_text = new UIText("score_text");
		this->attachChild(score_text);
		score_text->setPosition(0, -100);
		score_text->setText("      GOAL\n Score: " + to_string(ScoreManager::getInstance()->getScore()));	//game over win text
		score_text->setSize(50);
		button->setPosition(0, 100);
		button_1Text->setText("BACK");
	}
	//if quit screen instance
	else
	{
		//quit to main menu button
		UIText* displayText = new UIText("displayText");
		this->attachChild(displayText);
		displayText->setPosition(0, -100);
		displayText->setSize(40);
		displayText->setText("LEAVE RACE");
		displayText->setColorOutThickness(3);

		//no button
		button = new UIButton("no", btnNormal, btnPressed);
		this->attachChild(button);
		button->setPosition(150, 100);
		button->getTransformable()->setScale(0.3f, 0.3f);
		button->setButtonListener(this);

		UIText* button_2Text = new UIText("text_2");
		button->attachChild(button_2Text);
		button_2Text->setPosition(0, 0);
		button_2Text->setSize(60);
		button_2Text->setText("NO");
	}
	
	//pause
	ApplicationManager::getInstance()->pauseApplication();
	AudioManager::getInstance()->pauseAllSounds();
}

void QuitScreen::onButtonClick(UIButton* button)
{

}

void QuitScreen::onButtonReleased(UIButton* button)
{
	//  quit game
	if (button->getName() == "yes") {
		if (this->forMainMenu) {
			SceneManager::getInstance()->unloadScene();
			ApplicationManager::getInstance()->applicationQuit();
		}
		else 
		{ // exit to mainmenu
			SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
			PhysicsManager::getInstance()->destroy();
			ScoreManager::getInstance()->destroy();
			ApplicationManager::getInstance()->resumeApplication();
			AudioManager::getInstance()->stopAllSounds();
		}
	}
	// go back to the game and delete screen
	else if (button->getName() == "no") {
		ApplicationManager::getInstance()->resumeApplication();
		AudioManager::getInstance()->unpauseAllSounds();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}


void QuitScreen::markMainMenuQuit()
{
	this->forMainMenu = true;
}

void QuitScreen::markGameQuit()
{
	this->forMainMenu = false;
}