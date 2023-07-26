#include "EnemyAirplane.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"

EnemyAirplane::EnemyAirplane(string name, int level) : APoolable(name, level)
{

}

void EnemyAirplane::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTexture("avenger"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

}

void EnemyAirplane::onRelease()
{

}

void EnemyAirplane::onActivate()
{
	//reset state
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
}

APoolable* EnemyAirplane::clone()
{
	APoolable* copyObj = new EnemyAirplane(this->name);
	return copyObj;
}