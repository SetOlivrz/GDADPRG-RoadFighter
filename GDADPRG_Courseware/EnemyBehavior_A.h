
#pragma once
#include "AComponent.h"
class EnemyBehavior_A : public AComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1};

	EnemyBehavior_A(string name);
	void perform();
	void configure(float delay);
	void reset();
	void setSpeed(float speed);


private:
	 float SPEED_MULTIPLIER = -300.0f;
	 int direction = (rand() % 2) + 1;
	 EnemyMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};
