
#include "PlayerInputController.h"
#include "CarPlayer.h"

PlayerInputController::PlayerInputController(string name) : GenericInputController(name)
{

}

PlayerInputController::~PlayerInputController()
{
	GenericInputController::~GenericInputController();
}

void PlayerInputController::perform()
{
	CarPlayer* player = (CarPlayer*)this->getOwner();

	/* do not accept any input if the player:
		- skids
		- crashed
		- finished the course
	*/
	if(player->isSkidding()|| player->crashed || player->winCourse ||player->noFuel)
	{
		// disable all movements
		this->moveUp = false;
		this->moveLeft = false;
		this->moveRight = false;
	}

	//read player input
	else
	{
		bool keyFlag = false;	//key pressed flag
		if (event.type == sf::Event::KeyPressed) {
			keyFlag = true;
		}
		else if (event.type == sf::Event::KeyReleased) {
			keyFlag = false;
		}

		//setting move states
		switch (event.key.code) 
		{
			case sf::Keyboard::Space:
				this->moveUp = keyFlag;
				break;
			case sf::Keyboard::A:
				this->moveLeft = keyFlag;
				break;
			case sf::Keyboard::D:
				this->moveRight = keyFlag;
				break;
		}
	}
	
}

bool PlayerInputController::isUp()
{
	return this->moveUp;
}
bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}