#pragma once
#include "AComponent.h"
class EnemyBehavior_B :public AComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, SlowForward = 2, Side = 3 };

	EnemyBehavior_B(string name);
	void perform();
	void configure(float delay);
	void reset();
	void setSpeed(float speed);


private:
	 float SPEED_MULTIPLIER = -300.0f;
	 int direction = (rand() % 2) + 1;
	 EnemyMovementType movementType = Side;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
	float sideDuration = 0.3f;
	float sideCue = 0.f;
	
};


