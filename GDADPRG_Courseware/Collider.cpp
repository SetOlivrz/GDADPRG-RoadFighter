#include "Collider.h"
#include "CollisionListener.h"

Collider::Collider(string name):AComponent(name, Script)
{
}

void Collider::setCollisionListener(CollisionListener* listener)
{
	this->listener = listener;
}

// sets the checked bool
void Collider::setChecked(bool flag)
{
	this->checked = flag;
}

// returns the bool for checked attribute
bool Collider::isChecked()
{
	return this->checked;
}

// collision
bool Collider::willCollide(Collider* another)
{
	if (this->getGlobalBounds().intersects(another->getGlobalBounds()))
	{
		return true;
	}
	else
		return false;
}

// returns the collided
bool Collider::alreadyCollided()
{
	return collided;
}

// setter for collider attr
void Collider::setAlreadyCollided(bool flag)
{
	this->collided = flag;
}

//getter for the local bounds
sf::FloatRect Collider::getGlobalBounds()
{
	return localBounds;
}

// setter for the local bounds
void Collider::setLocalBounds(sf::FloatRect localBounds)
{
	this->localBounds = localBounds;
}

// calls the colliding func of the listener
void Collider::collisionEnter(AGameObject* gameObjects)
{
	this->listener->colliding(gameObjects);
}

void Collider::collisionEnter(int dir)
{
	this->listener->colliding(dir);
}

// collision
void Collider::collisionEnter()
{
	this->listener->collidingObstacle();
}

void Collider::collisionExit(AGameObject* gameObjects)
{
}

void Collider::perform()
{
}
