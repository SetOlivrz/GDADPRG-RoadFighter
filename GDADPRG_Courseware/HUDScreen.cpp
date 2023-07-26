#include "HUDScreen.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "UIText.h"
#include "QuitScreen.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"
#include "HUDUpdate.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include <iostream>

#include <string>

HUDScreen::HUDScreen(string name, int level) : AGameObject(name, level)
{
	this->level = level;
}

HUDScreen::~HUDScreen()
{
	AGameObject::~AGameObject();
}

void HUDScreen::initialize()
{
	string minimap;
	switch (level)
	{
		case 1: minimap = "sidemap_1"; break;
		case 2: minimap = "sidemap_2"; break;
		case 3: minimap = "sidemap_3"; break;
	}
	
	ARendererFactory* factory = new RendererFactory();


	sprite_main = new sf::Sprite();
	Renderer* renderer_main = factory->createSprite("HUDScreen","texture", "hud_bg", sprite_main);
	sprite_main->setScale(1.2f, 1.4f);	
	this->attachComponent(renderer_main);

	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);


	sprite_sidemap = new sf::Sprite();
	Renderer* renderer_sidemap = factory->createSprite("HUDSidemap","texture", minimap, sprite_sidemap);
	this->attachComponent(renderer_sidemap);

	sf::Vector2u textureSize_sidemap = this->sprite_sidemap->getTexture()->getSize();
	int leftAlignment = (int)(textureSize_sidemap.x / 2);
	sprite_sidemap->setOrigin(textureSize_sidemap.x / 2, textureSize_sidemap.y / 2);
	sprite_sidemap->setPosition(leftAlignment + (Game::WINDOW_WIDTH / 2) * -1, 0);
	//sprite_sidemap->setScale(1.2f, 1.4f);


	sprite_playerIcon = new sf::Sprite();
	Renderer* renderer_playerIcon = factory->createSprite("HUDIcon","spritesheet", "player_icon", sprite_playerIcon);
	this->attachComponent(renderer_playerIcon);
	sprite_playerIcon->setScale(.3, .3);

	iconPos = sf::Vector2f(((Game::WINDOW_WIDTH / 2) * -1) + leftAlignment, (Game::WINDOW_HEIGHT / 2)-75);
	sprite_playerIcon->setPosition(iconPos.x, iconPos.y);


	// button
	sf::Texture* btnNormal = TextureManager::getInstance()->getTexture("btn_normal");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTexture("btn_pressed");
	UIButton* quitBtn = new UIButton("quitBtn", btnNormal, btnPressed);
	this->attachChild(quitBtn);
	quitBtn->setPosition(400, 310);
	quitBtn->getTransformable()->setScale(0.25f, 0.20f);
	quitBtn->setButtonListener(this);

	// text
	UIText* button_1Text = new UIText("text_5");
	//do not make as a button child. difficult to position
	quitBtn->attachChild(button_1Text);
	button_1Text->setPosition(0, 10);
	button_1Text->setSize(75);
	button_1Text->setColorOutThickness(7);
	button_1Text->setText("QUIT");

	// speed text
	speedText = new UIText("speedText");
	//do not make as a button child. difficult to position
	this->attachChild(speedText);
	speedText->setPosition(360, -50 );
	speedText->setSize(20);
	speedText->setText(this->speed);

	// fuel text
	fuelText = new UIText("fuelText");
	//do not make as a button child. difficult to position
	this->attachChild(fuelText);
	fuelText->setPosition(360, 150);
	fuelText->setSize(20);
	fuelText->setText(this->fuel);

	// score text
	scoreText = new UIText("scoreText");
	//do not make as a button child. difficult to position
	this->attachChild(scoreText);
	scoreText->setPosition(360, -250);
	scoreText->setSize(20);
	scoreText->setColorOutThickness(4);
	scoreText->setText(this->score);

	// component for updating the stats
	HUDUpdate* hud = new HUDUpdate("HUDupdate");
	this->attachComponent(hud);

}

void HUDScreen::onButtonClick(UIButton* button)
{
}

void HUDScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "quitBtn") {
		QuitScreen* quitScreen = new QuitScreen("quitScreen");
		quitScreen->markGameQuit();
		GameObjectManager::getInstance()->addObject(quitScreen);
	}
}

void HUDScreen::setScoreDisp(float scr)
{
	this->score = to_string((int)scr);
	this->scoreText->setText("1P\n  " + score);;
}

void HUDScreen::setFuelDisp(float gas)
{
	this->fuel = to_string((int)gas);
	this->fuelText->setText("FUEL:\n  "+fuel);
}

void HUDScreen::setSpeedDisp(float spd)
{
	this->speed = to_string((int)spd);
	this->speedText->setText("km/h\n  "+speed);
}
void HUDScreen::setIconPos(float dis)
{
	this->sprite_playerIcon->setPosition(iconPos.x, iconPos.y - dis);
}

float HUDScreen::getIconPos()
{
	return this->sprite_playerIcon->getPosition().y;
}
//
//float CarPlayer::getFuel()
//{
//    return this->fuel;
//}
//
//void CarPlayer::updateFuel(float minusFuel)
//{
//    this->fuel -= minusFuel;
//}

