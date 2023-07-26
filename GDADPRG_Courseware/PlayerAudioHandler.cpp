#include "PlayerAudioHandler.h"
#include "AGameObject.h"
#include "PlayerInputController.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"
#include "AudioManager.h"
#include <iostream>

PlayerAudioHandler::PlayerAudioHandler(string name):AComponent(name, Script)
{
}

PlayerAudioHandler::~PlayerAudioHandler()
{
	AComponent::~AComponent();
}

void PlayerAudioHandler::perform()
{
	PlayerInputController* inputController = (PlayerInputController*)this->getOwner()->getComponentsOfType(ComponentType::Input)[0];
	CarPlayer* player = (CarPlayer*)this->getOwner();


	//conditions to play sound
	// ---------------------- START OF GAME---------------------------------//


	// countdown for level 1
	if (player->getLevel() == 1 && countdown == 0)	//countdown pahse
	{
		AudioManager::getInstance()->playSoundOnce("countdown");
		countdown++;
	}

	if (AudioManager::getInstance()->isPlaying("countdown"))	//disable all other player sounds
	{
		return;
	}

	// ---------------------- GAME OVER---------------------------------//
	// goal
	if (player->winCourse == true && playedFinishSFX == false)
	{
		playedFinishSFX = true;
		AudioManager::getInstance()->stopAllSounds();
		AudioManager::getInstance()->playSoundOnce("goal");
	}
	// no fuel
	else if(player->noFuel && playedFinishSFX == false)
	{
		playedFinishSFX = true;
		AudioManager::getInstance()->stopSound("fuel_warning");
	}

	// full stop no fuel
	if (player->getSpeed() == 0 && player->noFuel)
	{
		AudioManager::getInstance()->stopAllSounds();
	}


	// ----------------------PLAYER STATUS---------------------------------//
	// low fuel
	if (player->getFuel() < 10 && counter == 0)
	{
		counter++;
		AudioManager::getInstance()->playSoundOnce("fuel_warning");
	}
	// car crash
	if (player->crashed== true)
	{
		AudioManager::getInstance()->playSoundOnce("crash");
	}

	// skid
	if (player->isSkidding())
	{
		AudioManager::getInstance()->stopSound("accelerating");
		AudioManager::getInstance()->stopSound("max_speed");
		AudioManager::getInstance()->playSoundOnce("skidding");
	}
	else
	{
		AudioManager::getInstance()->stopSound("skidding");
	}

	// moving forward
	if (inputController->isUp()&& player->isSkidding()==false && (player->noFuel== false || player->getSpeed()!=0))
	{
		//accelerating
		if (player->getSpeed() < 700)
		{
			AudioManager::getInstance()->playSoundOnce("accelerating");
		}
		//top speed
		else
		{
			AudioManager::getInstance()->stopSound("accelerating");
			AudioManager::getInstance()->playSoundInLoop("max_speed");
		}
			
	}
	else
	{
		AudioManager::getInstance()->stopSound("accelerating");
		AudioManager::getInstance()->stopSound("max_speed");
	}

}
