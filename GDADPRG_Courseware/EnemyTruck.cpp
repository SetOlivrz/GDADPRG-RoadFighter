#include "EnemyTruck.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior_A.h"
#include <iostream>
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include"PhysicsManager.h"
#include "ScoreManager.h"
#include "Bounds.h"
#include "EnemyAudioHandler.h"
#include "CollisionListener.h"



EnemyTruck::EnemyTruck(string name, int level) :ACar(), APoolable(name, level), CollisionListener()
{

}

void EnemyTruck::initialize()
{
	this->setBounds(level);
	this->SKIDSPEED_MULTIPLIER = 15.f;

	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	this->transformable.setScale(.4, .4);
	Renderer* renderer = factory->createSprite("truck", "spritesheet", "truck", sprite);
	this->attachComponent(renderer);

	this->setPosition(this->center, -30); // offset
	this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0);//position

	//behavior
	EnemyBehavior_A* behavior = new EnemyBehavior_A("EnemyBehavior_E");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	// collider
	Collider* collider = new Collider("TruckCollider");
	collider->setLocalBounds(this->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	//bounds
	Bounds* bounds = new Bounds("TruckBounds");
	bounds->setLocalBounds(this->getGlobalBounds());
	this->attachComponent(bounds);

	EnemyAudioHandler* audioHandler = new EnemyAudioHandler("EnemyAudioHandler");
	this->attachComponent(audioHandler);

}

void EnemyTruck::onRelease()
{
}

void EnemyTruck::onActivate()
{
	//reset state
	EnemyBehavior_A* behavior = (EnemyBehavior_A*)this->findComponentByName("EnemyBehavior_E");
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

void EnemyTruck::colliding(AGameObject* object)
{
	
}

void EnemyTruck::colliding(int dir)
{
	this->skidding = true;
	this->direction = dir;
}

void EnemyTruck::nonColliding()
{
}

APoolable* EnemyTruck::clone()
{
	APoolable* copyObj = new EnemyTruck(this->name, this->level);
	return copyObj;
}
