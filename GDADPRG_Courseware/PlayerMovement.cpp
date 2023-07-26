#include "PlayerMovement.h"
#include "AGameObject.h"
#include "PlayerInputController.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"
#include "ScoreManager.h"
#include "TransitionScreen.h"
#include "AudioManager.h"
#include "QuitScreen.h"
#include <iostream>
#include "TextureManager.h"

PlayerMovement::PlayerMovement(string name) : AComponent(name, Script)
{

}

PlayerMovement::~PlayerMovement()
{
	AComponent::~AComponent();
}

void PlayerMovement::perform()
{
	timer += deltaTime.asSeconds();
	// delay for start
	if (this->getOwner()->getLevel() ==1 && AudioManager::getInstance()->isPlaying("countdown") || AudioManager::getInstance()->isPlaying("goal"))
	{
		return;
	}
	else if (this->getOwner()->getLevel() >1)
	{
		if (timer < 2)
		{
			return;
		}
	}

	PlayerInputController* inputController = (PlayerInputController*)this->getOwner()->getComponentsOfType(ComponentType::Input)[0];	//get player's playerInputController component
	CarPlayer* player = (CarPlayer*)this->getOwner();	//get player's car object
	sf::Transformable* playerTransformable = this->getOwner()->getTransformable();		//get player's transformable component
	sf::Vector2f offset(0.0f, 0.0f);

	if (playerTransformable == NULL || inputController == NULL)
	{
		std::cout << "One or more of the needed dependencies are missing!\n";
		return;
	}
	
	// ---------------------- CRASH---------------------------------/
	if (player->crashed == true)
	{
		player->stopSkidding();	//end skid
		ticks += deltaTime.asSeconds();
		frame++;
		// crash animation
		switch (frame % 3)
		{
			case 1: TextureManager::getInstance()->getFrame("crash1", this->getOwner()->getSprite()); break;
			case 2: TextureManager::getInstance()->getFrame("crash2", this->getOwner()->getSprite()); break;
			case 3: TextureManager::getInstance()->getFrame("crash3", this->getOwner()->getSprite()); break;
		}
		if (ticks > 0.7f)
		{
			TextureManager::getInstance()->getFrame("player", this->getOwner()->getSprite());
			player->crash(false);
		}
	}

	// ---------------------- SKID---------------------------------/
	if(player->isSkidding() && player->winCourse == false)
	{
		cout << "Player SKidding";
		ticks += deltaTime.asSeconds();
		if(ticks < .8f)	//if(animationCount > 8)
		{
			player->setSpeed(player->getSpeed() - deltaTime.asSeconds() * 200); // decelarate

			switch (player->getDirection())
			{
				case 1: offset.x -= player->SKIDSPEED_MULTIPLIER; TextureManager::getInstance()->getFrame("skidLeft", this->getOwner()->getSprite()); break;
				case 2: offset.x += player->SKIDSPEED_MULTIPLIER; TextureManager::getInstance()->getFrame("skidRight", this->getOwner()->getSprite());  break;
			}
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
		else
		{
			TextureManager::getInstance()->getFrame("player", this->getOwner()->getSprite());
			player->stopSkidding();
			ticks = 0.0f;
		}
	}

	// PLAYER INPUTS
	else if (player->winCourse == false && player->loseCourse== false)
	{
		if (inputController->isUp()&& player->noFuel== false) // accelerate
		{
			player->setSpeed(player->getSpeed() + deltaTime.asSeconds() * 250);
		}
		else
		{
			player->setSpeed(player->getSpeed() - deltaTime.asSeconds() * 150); // decelerate
		}

		if (inputController->isRight()) // right
		{
			offset.x += this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
		else if (inputController->isLeft()) // left
		{
			offset.x -= this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
	
	// ---------------------- WIN AND LOSE BEHAVIOR---------------------------------/

	if (player->winCourse)
	{
		player->stopSkidding();
		offset.y -= 200;
		playerTransformable->move(offset * deltaTime.asSeconds());

		// if the player is outside the screen
		if (playerTransformable->getPosition().y < -15 && callScreen == false)
		{
			// calls the an object screen every after end of the course
			if (player->getLevel() < 3)
			{
				TransitionScreen* screen = new TransitionScreen("transition_scr", player->getLevel());
				GameObjectManager::getInstance()->addObject(screen);
			}
			else
			{
				QuitScreen* endScreen = new QuitScreen("end_screen");
				GameObjectManager::getInstance()->addObject(endScreen);
				endScreen->initialize();
			}
			callScreen = true;
		}
	}
	// decrease speed when no fuel
	else if (player->loseCourse == true)
	{
		if (callScreen == false)
		{
			QuitScreen* loseScreen = new QuitScreen("lose_screen");
			GameObjectManager::getInstance()->addObject(loseScreen);
			loseScreen->initialize();
			callScreen = true;
		}
	}
	
	// ---------------------- CLAMPS---------------------------------/

	// bounds clamp
	if(playerTransformable->getPosition().x > player->rightBounds)
	{
		playerTransformable->setPosition(player->rightBounds, playerTransformable->getPosition().y);
	}
	else if(playerTransformable->getPosition().x < player->leftBounds)
	{
		playerTransformable->setPosition(player->leftBounds, playerTransformable->getPosition().y);
	}

	// speed clamp
	if (player->getSpeed() > 1000)
	{
		player->setSpeed(1000);
	}
	
	if (player->getSpeed() < 0)
	{
		player->setSpeed(0);
	}


	// ------------------------------ CRASH ---------------------------------/

	// crash if all are true
	// - skidding to boundary
	// - in boundary plus input
	// speed >= 800

	bool leftMost = playerTransformable->getPosition().x <= player->leftBounds;
	bool rightMost = playerTransformable->getPosition().x >= player->rightBounds;

	bool crashLeft = player->getSpeed() >= 800 && leftMost && inputController->isLeft();
	bool crashRight = player->getSpeed() >= 800 && rightMost && inputController->isRight();

	if ((player->isSkidding() && (leftMost || rightMost)) || crashLeft || crashRight )
	{
		player->crash(true);
		this->ticks = 0.0f;
	}

	// -------------------- WINNING AND LOSING CONDITION ---------------------------/
	if (player->getDistTrav() >= 55 && player->winCourse == false)
	{
		player->setSpeed(0.f);
		player->winCourse = true;
		ScoreManager::getInstance()->updateScore(1000);
	}
	else if (player->getFuel() == 0 && player->winCourse == false)
	{
		player->setSpeed(player->getSpeed() - deltaTime.asSeconds() * 150);
		if (player->getSpeed() <= 0)
		{
			player->loseCourse = true;
			AudioManager::getInstance()->stopAllSounds();
		}
	}

	// ---------------------- UPDATE PLAYER STATS ---------------------------------/
	if (player->winCourse==false && player->loseCourse == false)
	{
		player->updateFuel(deltaTime.asSeconds() * 1.5);
		if (player->getFuel() <= 0)
		{
			player->setFuel(0);
			player->noFuel = true;
		}
	}
	player->addDistTrav(player->getSpeed()* deltaTime.asSeconds());

	cout << "Speed: " << player->getSpeed() << "  Dist: " << player->getDistTrav() <<"   POS: "<< player->getTransformable()->getPosition().x <<" \n";
}