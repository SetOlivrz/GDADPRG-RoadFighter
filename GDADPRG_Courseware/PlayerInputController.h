#pragma once
#include "GenericInputController.h"

class PlayerInputController : public GenericInputController
{
public:
	PlayerInputController(string name);
	~PlayerInputController();

	void perform();
	bool isUp();
	bool isDown();
	bool isLeft();
	bool isRight();

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
};
