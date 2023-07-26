#pragma once
#include "APoolable.h"
class EnemyAirplane : public APoolable
{
public:
	EnemyAirplane(string name);
	void initialize();
	void onRelease();
	void onActivate();
	APoolable* clone();

private:
	int counter = 0;
};