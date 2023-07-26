#pragma once
#include "AComponent.h"
class EnemySwarmHandler_C : public AComponent
{
public:
	EnemySwarmHandler_C(int numEnemies, string name, int level, float interval);
	~EnemySwarmHandler_C();
	void perform();

private:
	float SPAWN_INTERVAL = 0.f;
	float ticks = 0.0f;
	int level = 0;
};
