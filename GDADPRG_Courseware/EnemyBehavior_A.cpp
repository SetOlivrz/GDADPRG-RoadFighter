#include "EnemyBehavior_A.h"
#include "AGameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "GameObjectManager.h"
#include "CarPlayer.h"
#include "EnemyCar_A.h"

EnemyBehavior_A::EnemyBehavior_A(string name) : AComponent(name, Script)
{
	this->reset();
}

void EnemyBehavior_A::perform()
{
	float playerSpeed = 0;
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");
	EnemyCar_A* head = (EnemyCar_A*)this->getOwner();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	playerSpeed = player->getSpeed();

	// skid movement
	if(head->isSkidding())
	{
		this->ticks += this->deltaTime.asSeconds();
		if (this->ticks < 0.7f)
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
			head->stopSkidding();
			this->ticks = 0.0f;
		}
	}

	// forward movement
	if (this->movementType == Forward) {

		transformable->move(0, (this->deltaTime.asSeconds() * (SPEED_MULTIPLIER + playerSpeed)));
	}
	
	// release condition
	if (transformable->getPosition().y> Game::WINDOW_HEIGHT + 20  || transformable->getPosition().y < -80)
	{
		//check owner type

		if(this->getOwner()->getName() == "enemy")
		{
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_A_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
			std::cout << "released\n";
		}
		
		else if(this->getOwner()->getName() == "bonusCar")
		{
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_D_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
			std::cout << "released\n";
		}

		else if(this->getOwner()->getName() == "truck")
		{
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_E_POOL_TAG)->releasePoolable((APoolable*)this->getOwner());
			std::cout << "released\n";
		}

	}
	//TEMPORARY: just here to check if setEnabled flags work
	/*if (this->ticks > this->delay) {
		this->getOwner()->setEnabled(false);
	}*/

}

void EnemyBehavior_A::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior_A::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	this->forwardDuration = (rand() % 3) + 1.0f; // randomized forward duration
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}

void EnemyBehavior_A::setSpeed(float speed)
{
	this->SPEED_MULTIPLIER = speed;
}
