#include "BGObject.h"
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "BGMovement.h"

BGObject::BGObject(std::string name, int level) : AGameObject(name, level) 
{}

void BGObject::initialize()
{
	string course_bg = "NONE";

	//set bg according to level
	switch (level)
	{
	case 1: course_bg = "course_1_bg"; break;
	case 2: course_bg = "course_2_bg"; break;
	case 3: course_bg = "course_3_bg"; break;
	}
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture(course_bg));
	sprite->setOrigin(sprite->getTexture()->getSize().x / 2, 0);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	getTransformable()->setPosition(Game::WINDOW_WIDTH/2, -Game::WINDOW_HEIGHT);

	BGMovement* movement = new BGMovement("BG_Movement");
	this->attachComponent(movement);

	Renderer* renderer = new Renderer("BG");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
}

