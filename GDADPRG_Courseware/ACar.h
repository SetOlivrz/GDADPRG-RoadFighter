#pragma once
class ACar
//all car objects
{
public:
	ACar();
	void stopSkidding();
	bool isSkidding();
	void setDirection(int dir);
	int getDirection();
	void setBounds(int level);

	float SKIDSPEED_MULTIPLIER = 100; // speed for skidding
	// map bounds
	 int rightBounds = 100;
	 int leftBounds = -100;
	 int rangeInX = ((rightBounds - leftBounds) / 2);
	 float center = 0;

	 bool crashed = false;
protected:
	bool skidding = false;;
	int direction = 0;

};