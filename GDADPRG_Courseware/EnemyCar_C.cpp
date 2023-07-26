#include "EnemyCar_C.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior_C.h"
#include <iostream>
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "Bounds.h"
#include "EnemyAudioHandler.h"


EnemyCar_C::EnemyCar_C(string name, int level) :ACar(), APoolable(name, level), CollisionListener()
{
	this->setBounds(level);

	//assign texture
	sprite = new sf::Sprite();
	ARendererFactory* factory = new RendererFactory();
	Renderer* renderer = factory->createSprite("EnemyCarC", "spritesheet", "enemy_car3", sprite);
	this->transformable.setScale(.4, .4);

	this->attachComponent(renderer);

	this->setPosition(center, -30); // offset
	this->getTransformable()->move(rand() % rangeInX - rand() % rangeInX, 0); // position

	//behavior
	EnemyBehavior_C* behavior = new EnemyBehavior_C("EnemyBehavior_C");
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

	EnemyAudioHandler* audioHandler = new EnemyAudioHandler("EnemyAudioHandler");
	this->attachComponent(audioHandler);
}

void EnemyCar_C::initialize()
{
}

void EnemyCar_C::onRelease()
{
}

void EnemyCar_C::onActivate()
{
	//reset state
	EnemyBehavior_C* behavior = (EnemyBehavior_C*)this->findComponentByName("EnemyBehavior_C");
	behavior->reset();
	this->setPosition(center, -30);

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
void EnemyCar_C::colliding(AGameObject* object)
{
	this->skidding = true;

}


//collision effect
void EnemyCar_C::colliding(int dir)
{
	this->skidding = true;
	this->direction = dir;
}

void EnemyCar_C::nonColliding()
{
}

APoolable* EnemyCar_C::clone()
{
	APoolable* copyObj = new EnemyCar_C(this->name, this->level);
	return copyObj;
}
