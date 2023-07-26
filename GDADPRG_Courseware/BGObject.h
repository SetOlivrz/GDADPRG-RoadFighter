#pragma once
#include "AGameObject.h"
class BGObject : public AGameObject
{
public:
	BGObject(std::string name, int level);
	void initialize();
private:
	const float SPEED_MULTIPLIER = 100.0f;
};

