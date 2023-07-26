#pragma once
#include "AComponent.h"
//class handling N enemy airplanes. communicates with object pool
class EnemySwarmHandler_D : public AComponent
{
public:
	EnemySwarmHandler_D(int numEnemies, string name, int level, float interval);
	~EnemySwarmHandler_D();
	void perform();

private:
	float SPAWN_INTERVAL = 0;
	float ticks = 0.0f;
	int level = 0;
	int instances;
	float distanceCounter;
};