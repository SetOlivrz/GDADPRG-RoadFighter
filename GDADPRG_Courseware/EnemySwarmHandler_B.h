#pragma once
#include "AComponent.h"
class EnemySwarmHandler_B :
    public AComponent
{
public:
	EnemySwarmHandler_B(int numEnemies, string name, int level, float interval);
	~EnemySwarmHandler_B();
	void perform();

private:
	float SPAWN_INTERVAL = 0.f;
	float ticks = 0.0f;
	int level = 0;
};

