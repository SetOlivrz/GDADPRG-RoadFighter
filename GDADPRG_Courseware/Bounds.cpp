#include "Bounds.h"

Bounds::Bounds(string name) :AComponent(name, Script)
{
}

void Bounds::setBoundsListener(BoundsListener* listener)
{
	this->listener = listener;
}

void Bounds::setChecked(bool flag)
{
    this->checked = flag;
}

bool Bounds::isChecked()
{
    return checked;
}

// checks for overtakes
bool Bounds::willOvertake(Bounds* another)
{
    // if owner is higher than the object from paramter (owner y > object y)
    if (this->getGlobalBounds().top < another->getGlobalBounds().top)
        return true;
    else
        return false;
}

// returns overtake status
bool Bounds::alreadyOvertaken()
{
    return overtaken;
}

// sets the overtaken attribute
void Bounds::setAlreadyOvertaken(bool flag)
{
    this->overtaken = flag;
}

// returns local bounds
sf::FloatRect Bounds::getGlobalBounds()
{
    return localBounds;
}

// setter for local bounds
void Bounds::setLocalBounds(sf::FloatRect localBounds)
{
    this->localBounds = localBounds;
}

void Bounds::perform()
{
}
