#pragma once
#include "AComponent.h"
class EnemyAudioHandler : public AComponent
{
public:

	EnemyAudioHandler(string name);
	~EnemyAudioHandler();

	void perform();

private:
	const float SPEED_MULTIPLIER = 250.0f;
	float timer = 0;
	float timerDuration = 5;
	float ticks = 0;
	float countdown = 0;
	bool  callScreen = false;
	int counter = 0;


};

