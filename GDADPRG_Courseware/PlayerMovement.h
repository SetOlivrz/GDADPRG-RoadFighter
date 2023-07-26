
#pragma once
#include "AComponent.h"
class PlayerMovement : public AComponent
{
public:
	PlayerMovement(string name);
	~PlayerMovement();

	void perform();

private:
	const float SPEED_MULTIPLIER = 250.0f;
	float timer = 0;
	float ticks = 0;
	float countdown = 0;
	bool  callScreen = false;
	int counter = 0;
	int frame = 0;
	int animationFrame = 0;
};
