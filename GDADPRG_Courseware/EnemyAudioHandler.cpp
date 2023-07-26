#include "EnemyAudioHandler.h"
#include "AGameObject.h"
#include "GameObjectManager.h"
#include "AudioManager.h"
#include <iostream>
#include "EnemyCar_A.h"
#include "EnemyCar_B.h"
#include "EnemyCar_C.h"
#include "BonusCar.h"
#include "EnemyTruck.h"

EnemyAudioHandler::EnemyAudioHandler(string name) :AComponent(name, Script)
{
}

EnemyAudioHandler::~EnemyAudioHandler()
{
	AComponent::~AComponent();
}

void EnemyAudioHandler::perform()
{
	string ownerName = this->getOwner()->getName();

	//getting and setting owner type

	EnemyCar_A* car = (EnemyCar_A*)this->getOwner();

	if (ownerName == "EnemyCarB")
	{
		(EnemyCar_B*)car;
	}
	else if (ownerName == "EnemyCarC")
	{
		(EnemyCar_B*)car;
	}
	else if (ownerName == "BonusCar")
	{
		(BonusCar*)car;
	}
	else if (ownerName == "truck")
	{
		(EnemyTruck*)car;
	}
	

	//conditions to play sound
	if (car->isSkidding())	//skidding
	{
		AudioManager::getInstance()->playSoundOnce("collide");
	}

}