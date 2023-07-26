#pragma once
#include "AGameObject.h"

class CollisionListener {

public:
	virtual void colliding(AGameObject* object) = 0;
	virtual void nonColliding() = 0;

	virtual void crash() {};
	virtual void colliding(int dir) {};
	virtual void collidingObstacle() {};
protected:
	CollisionListener() {}
};