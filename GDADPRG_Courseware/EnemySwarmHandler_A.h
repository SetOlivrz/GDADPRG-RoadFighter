
#pragma once
#include "AComponent.h"
//class handling N enemy airplanes. communicates with object pool
class EnemySwarmHandler_A : public AComponent
{
public:
	EnemySwarmHandler_A(int numEnemies, string name, int level, float interval);
	~EnemySwarmHandler_A();
	void perform();

private:
	float SPAWN_INTERVAL = 0;
	float ticks = 0.0f;
	int level = 0;
};