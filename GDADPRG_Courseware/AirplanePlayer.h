
#pragma once
#include "AGameObject.h"
#include <iostream>

using namespace std;

class AirplanePlayer : public AGameObject
{
public:
	AirplanePlayer(string name);
	void initialize();
private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

};

