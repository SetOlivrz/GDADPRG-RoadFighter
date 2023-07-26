#include "SamplePopupScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "Renderer.h"

SamplePopupScreen::SamplePopupScreen(string name, int level) :AGameObject(name, level), ButtonListener()
{

}

SamplePopupScreen::~SamplePopupScreen()
{
	AGameObject::~AGameObject();
}

void SamplePopupScreen::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("ui_bg"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	//sprite_main->setColor(sf::Color::Cyan);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	this->getTransformable()->setScale(0.75f, 0.75f);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(0, 100);
	button->getTransformable()->setScale(0.3f, 0.3f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(0, -20);
	button_1Text->setSize(100);
	button_1Text->setText("CLOSE");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(0, -100);
	displayText->setSize(40);
	displayText->setText("Hello World!");
}

void SamplePopupScreen::onButtonClick(UIButton* button)
{

}

void SamplePopupScreen::onButtonReleased(UIButton* button)
{
	GameObjectManager::getInstance()->deleteObject(this);
}