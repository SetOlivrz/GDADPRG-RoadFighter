#pragma once
#include "AComponent.h"
class PlayerAudioHandler : public AComponent
{
public:
	PlayerAudioHandler(string name);
	~PlayerAudioHandler();

	void perform();

private:
	const float SPEED_MULTIPLIER = 250.0f;
	float timer = 0;
	float timerDuration = 5;
	float ticks = 0;
	float countdown = 0;
	bool  callScreen = false;
	int counter = 0;

	bool playedFinishSFX = false;
};

