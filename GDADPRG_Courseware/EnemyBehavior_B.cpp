#include "EnemyBehavior_B.h"
#include "AGameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "GameObjectManager.h"
#include "CarPlayer.h"
#include "EnemyCar_B.h"
EnemyBehavior_B::EnemyBehavior_B(string name) : AComponent(name, Script)
{
	this->reset();
}

void EnemyBehavior_B::perform()
{

	// timer
	this->ticks += this->deltaTime.asSeconds();
	float playerSpeed = 0;

	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");
	EnemyCar_B* head = (EnemyCar_B*)this->getOwner();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	playerSpeed = player->getSpeed();


	// skidding
	if (head->isSkidding())
	{
		this->ticks += this->deltaTime.asSeconds();
		if (this->ticks < 0.7f)	//skidding stopwatch
		{
			if (head->getDirection() == 1)//left
			{
				if (transformable->getPosition().x > head->leftBounds)
					transformable->move(-1 * head->SKIDSPEED_MULTIPLIER * deltaTime.asSeconds(), 0.0f);

			}
			else if (head->getDirection() == 2)// right
			{
				if (transformable->getPosition().x < head->rightBounds)
					transformable->move(head->SKIDSPEED_MULTIPLIER * deltaTime.asSeconds(), 0.0f);
			}
		}
		else
		{
			head->stopSkidding();	//end skidding
			this->ticks = 0.0f;
		}
	}

	//move side when if in certain part of the screen
	if (this->movementType == Forward && transformable->getPosition().y >= sideCue) 
	{
		this->movementType = Side;
		this->ticks = 0.0f;
	}

	//moving side duration
	if (this->ticks > this->sideDuration && this->movementType == Side) {
		this->movementType = SlowForward;
		this->ticks = 0.0f;
	}

	if (this->movementType == Forward) {
		transformable->move(0, (this->deltaTime.asSeconds() * (SPEED_MULTIPLIER + playerSpeed)));
	}

	//post side move
	else if (this->movementType == SlowForward) {
		transformable->move(0, (this->deltaTime.asSeconds() * (SPEED_MULTIPLIER + playerSpeed)));
	}
	else if (this->movementType == Side) 
	{
		//move to pre-randomized side
		if (direction == 1)// right
		{
			if (transformable->getPosition().x < head->rightBounds)
				transformable->move(-this->deltaTime.asSeconds() * SPEED_MULTIPLIER / 2 * 1.5, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER + playerSpeed));
			else
				direction = 2;
		}
		else if (direction == 2 )// left
		{
			if (transformable->getPosition().x >head->leftBounds)
			transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER / 2 * 1.5, this->deltaTime.asSeconds() * (SPEED_MULTIPLIER + playerSpeed));
			else
				direction = 1;
		}
		else
		{
			cout << "error\n\n";
		}

	}
	if (transformable->getPosition().y> Game::WINDOW_HEIGHT + 20 || transformable->getPosition().y < -80) 
	{
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_B_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
			std::cout << "released\n";
	}
}

void EnemyBehavior_B::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior_B::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	this->sideCue = (rand() % 100) + 375.0f; // randomized forward duration
	this->forwardDuration = (rand() % 1) + 2.0f; // randomized forward duration
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}

void EnemyBehavior_B::setSpeed(float speed)
{
	this->SPEED_MULTIPLIER = speed;
}