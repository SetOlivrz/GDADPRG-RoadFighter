#pragma once
#include "AComponent.h"
class EnemySwarmHandler_E : public AComponent
{
public:
	EnemySwarmHandler_E(int numEnemies, string name, int level, float interval);
	~EnemySwarmHandler_E();
	void perform();

private:
	float SPAWN_INTERVAL = 0;
	float ticks = 0.0f;
	int level = 0;
};

