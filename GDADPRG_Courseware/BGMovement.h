#pragma once
#include "AComponent.h"
class BGMovement : public AComponent
{
public:
	BGMovement(string name);
	~BGMovement();
	void perform();
	void setSpeed(float speed);

private:
	 int counter = 0;
	 float SPEED_MULTIPLIER = 300.0f;
};