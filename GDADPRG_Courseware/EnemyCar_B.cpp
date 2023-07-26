#include "EnemyCar_B.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior_B.h"
#include <iostream>
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "Bounds.h"
#include "EnemyAudioHandler.h"

EnemyCar_B::EnemyCar_B(string name, int level):APoolable(name, level)
{
	
}

void EnemyCar_B::initialize()
{
	this->setBounds(level);

	//assign texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	Renderer* renderer = factory->createSprite("EnemyCarB", "spritesheet", "enemy_car2", sprite);
	this->transformable.setScale(.4, .4);
	this->attachComponent(renderer);

	this->setPosition(this->center, -30); // offset
	this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0); // position

	//behavior
	EnemyBehavior_B* behavior = new EnemyBehavior_B("EnemyBehavior_B");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	// collider
	Collider* collider = new Collider("EnemyCollider");
	collider->setLocalBounds(this->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	// bounds
	Bounds* bounds = new Bounds("EnemyBounds");
	bounds->setLocalBounds(this->getGlobalBounds());
	this->attachComponent(bounds);

	// audio handler
	EnemyAudioHandler* audioHandler = new EnemyAudioHandler("EnemyAudioHandler");
	this->attachComponent(audioHandler);
}

void EnemyCar_B::onRelease()
{
}

void EnemyCar_B::onActivate()
{
	//reset state
	EnemyBehavior_B* behavior = (EnemyBehavior_B*)this->findComponentByName("EnemyBehavior_B");
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


//collision effect
void EnemyCar_B::colliding(AGameObject* object)
{
	this->skidding = true;
}


//collision effect
void EnemyCar_B::colliding(int dir)
{
	this->skidding = true;
	this->direction = dir;
}

void EnemyCar_B::nonColliding()
{
	
}

APoolable* EnemyCar_B::clone()
{
	APoolable* copyObj = new EnemyCar_B(this->name, this->level);
	return copyObj;
}
