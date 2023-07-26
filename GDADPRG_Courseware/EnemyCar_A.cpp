#include "EnemyCar_A.h"
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

EnemyCar_A::EnemyCar_A(string name, int level):ACar(), APoolable(name, level), CollisionListener()
{
	
}

void EnemyCar_A::initialize()
{
	this->setBounds(level);
	
	// assign texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	this->transformable.setScale(.4, .4);
	Renderer* renderer = factory->createSprite("EnemyCarA", "spritesheet", "enemy_car1", sprite);
	this->attachComponent(renderer);

	// position
	this->setPosition(this->center, -30); // offset
	if (level < 3)
	{
		this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0);//position
	}
	else
	{
		switch (rand() % 2)
		{
		case 0: this->getTransformable()->move(-50, 0);
		case 1: this->getTransformable()->move(+50, 0);
		}
	}
	//behavior
	EnemyBehavior_A* behavior = new EnemyBehavior_A("EnemyBehavior_A");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	// collider
	Collider* collider = new Collider("EnemyCollider");
	collider->setLocalBounds(this->getGlobalBounds());
	collider->setCollisionListener(this);
	this->attachComponent(collider);

	//bounds
	Bounds* bounds = new Bounds("EnemyBounds");
	bounds->setLocalBounds(this->getGlobalBounds());
	this->attachComponent(bounds);

	EnemyAudioHandler* audioHandler = new EnemyAudioHandler("EnemyAudioHandler");
	this->attachComponent(audioHandler);

}

void EnemyCar_A::onRelease()
{
}

void EnemyCar_A::onActivate()
{
	//reset state
	EnemyBehavior_A* behavior = (EnemyBehavior_A*)this->findComponentByName("EnemyBehavior_A");
	behavior->reset();
	this->setPosition(this->center, -30);
	//randomize
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
void EnemyCar_A::colliding(AGameObject* object)
{
}


//collision effect
void EnemyCar_A::colliding(int dir)
{
	this->skidding = true;
	this->direction = dir;
}

void EnemyCar_A::nonColliding()
{
}

APoolable* EnemyCar_A::clone()
{
	APoolable* copyObj = new EnemyCar_A(this->name, this->level);
	return copyObj;
}
