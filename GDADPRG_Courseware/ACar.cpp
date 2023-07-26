#include "ACar.h"
//all car objects
ACar::ACar()	
{
}
// set skid to false
void ACar::stopSkidding()
{
	this->skidding = false;
    this->direction = 0;
}
// return skid bool
bool ACar::isSkidding()
{
	return this->skidding;
}
// setter for the direction
void ACar::setDirection(int dir)
{
	this->direction = dir;
}
// getter for the direction
int ACar::getDirection()
{
	return this->direction;
}
//setting the bounds of the map
void ACar::setBounds(int level)
{
	switch (level)
	{
		case 1: leftBounds = 412; rightBounds = 612; break;
		case 2: leftBounds = 412; rightBounds = 612; break;
		case 3: leftBounds = 405; rightBounds = 475; break;
		

	}
	center = ((leftBounds + rightBounds) / 2) - 15;

}
