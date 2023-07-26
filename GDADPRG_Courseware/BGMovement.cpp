#include "BGMovement.h"
#include "Game.h"
#include "AGameObject.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"
#include "TextureManager.h"
#include<iostream>
BGMovement::BGMovement(string name) : AComponent(name, Script)
{

}

BGMovement::~BGMovement()
{
	AComponent::~AComponent();
}

void BGMovement::perform()
{

	float playerSpeed = 0;
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");
	playerSpeed = player->getSpeed();
	setSpeed(playerSpeed);

	//make BG scroll slowly
	sf::Vector2f offset(0.0f, 0.0f);
	offset.y += SPEED_MULTIPLIER;
	this->getOwner()->getTransformable()->move(offset * deltaTime.asSeconds());


	sf::Vector2f localPos = this->getOwner()->getTransformable()->getPosition();

	if ((localPos.y) > 0) {
		counter++;

		//reset position
		this->getOwner()->getTransformable()->setPosition(Game::WINDOW_WIDTH / 2, - Game::WINDOW_HEIGHT); // reset position
		std::cout << this->getOwner()->getTransformable()->getPosition().y << " possssss\n";
	}
	
	int level = this->getOwner()->getLevel();
	string last_bg;


	switch (level)
	{
		case 1: last_bg = "finish_1_bg"; break;
		case 2: last_bg = "finish_2_bg"; break;
		case 3: last_bg = "finish_3_bg"; break;	
	}
	// 70 last loop

	//level 1 change bg animation
	if (level == 1)
	{
		switch (counter)
		{
			case 1: (this->getOwner()->getSprite()->setTexture(*TextureManager::getInstance()->getTexture("course_1.2_bg"))); break;
			case 39: (this->getOwner()->getSprite()->setTexture(*TextureManager::getInstance()->getTexture("course_1.3_bg"))); break;
			case 40: (this->getOwner()->getSprite()->setTexture(*TextureManager::getInstance()->getTexture("course_1.4_bg"))); break;
		}
	}



	//finish line
	switch (counter)
	{
		case 70: (this->getOwner()->getSprite()->setTexture(*TextureManager::getInstance()->getTexture(last_bg))); break;
	}
}

void BGMovement::setSpeed(float speed)
{
	this->SPEED_MULTIPLIER = speed;
}
