#pragma once
#include "AGameObject.h"
#include "CollisionListener.h"
#include "ACar.h"
#include "Renderer.h"


class CarPlayer : public ACar, public AGameObject, public CollisionListener
{
public:
	CarPlayer(string name, int level);
	void initialize();

	float getSpeed();
	float getFuel();
	float getScore();
	float getDistTrav();

	void setFuel(float fuel);

	void setSpeed(float spd);
	void addDistTrav(float dist);
	void addScore(int scr);
	void updateFuel(float gas);
	void addFuel(float gas);


	bool winCourse = false;
	bool loseCourse = false;
	bool noFuel = false;
	void crash(bool flag);

private:
	float disTravelled = 0;
	float fuel =100 ;

	bool moveUp = false;
	bool moveRight = false;
	bool moveLeft = false;

	void nonColliding();
	void colliding(AGameObject* object); //for releasing
	void colliding(int dir); // for skiding
	void collidingObstacle(); // for crashing

	float SPEED_MULTIPLIER = 0;
	sf::Texture texture;
	Renderer* renderer;
};



