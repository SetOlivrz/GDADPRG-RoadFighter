#include "BonusCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior_A.h"
#include <iostream>
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "Bounds.h"
#include "EnemyAudioHandler.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "AudioManager.h"
#include "ScoreManager.h"

BonusCar::BonusCar(string name, int level) :ACar(), APoolable(name, level), CollisionListener()
{

}

void BonusCar::initialize()
{
	this->setBounds(level);

	//assign texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	this->transformable.setScale(.3, .35);
	Renderer* renderer = factory->createSprite("bonusCar", "spritesheet", "bonus_car", sprite);
	this->attachComponent(renderer);

	//set initial position
	this->setPosition(this->center, -30); // offset
	this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0);//position

	//behavior (copies behabior of basic car)
	EnemyBehavior_A* behavior = new EnemyBehavior_A("EnemyBehavior_D");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	// collider
	Collider* collider = new Collider("bonusCarCollider");
	collider->setLocalBounds(this->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	//bounds
	Bounds* bounds = new Bounds("EnemyBounds");
	bounds->setLocalBounds(this->getGlobalBounds());
	this->attachComponent(bounds);

	//audio handler
	EnemyAudioHandler* audioHandler = new EnemyAudioHandler("EnemyAudioHandler");
	this->attachComponent(audioHandler);

}

void BonusCar::onRelease()
{
}

void BonusCar::onActivate()
{
	//reset state
	EnemyBehavior_A* behavior = (EnemyBehavior_A*)this->findComponentByName("EnemyBehavior_D");
	behavior->reset();
	this->setPosition(this->center, -30);

	if (this->level != 3)
	{
		//randomize between road with
		this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0);
	}
	else
	{
		//randomize between 2 lanes
		switch(rand()%2)
		{
			case 0: this->getTransformable()->move(-50, 0);
			case 1: this->getTransformable()->move(+50, 0);
		}
		
	}
}

//play sound and disappear
void BonusCar::colliding(AGameObject* object)
{
	ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_D_POOL_TAG)->releasePoolable(this);
	AudioManager::getInstance()->playSoundOnce("bonus_car");
	ScoreManager::getInstance()->updateScore(1000);
}

void BonusCar::colliding(int dir)
{
	this->skidding = true;
	this->direction = dir;
}

void BonusCar::nonColliding()
{
}

APoolable* BonusCar::clone()
{
	APoolable* copyObj = new BonusCar(this->name, this->level);
	return copyObj;
}
