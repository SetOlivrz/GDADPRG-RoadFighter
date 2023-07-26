#pragma once
#include "APoolable.h"
#include "CollisionListener.h"
#include "ACar.h"
class EnemyCar_A : public ACar, public APoolable, public CollisionListener
{
public:
	EnemyCar_A(string name, int level);
	void initialize();
	void onRelease();
	void onActivate();
	void colliding(AGameObject* object);
	void colliding(int dir);
	void nonColliding();
	APoolable* clone();

private:
	int counter = 0;
};