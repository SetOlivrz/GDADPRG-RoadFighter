#pragma once
#include "AComponent.h"
#include "CollisionListener.h"
#include "AGameObject.h"
class Collider : public AComponent {

public:
	
	Collider(string name);

	void setCollisionListener(CollisionListener* listener);

	void setChecked(bool flag);
	bool isChecked();

	bool willCollide(Collider* another);
	bool alreadyCollided();
	void setAlreadyCollided(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);
	// collision
	void collisionEnter(AGameObject* gameObjects); // for removing 
	void collisionEnter(int dir); // for skidding
	void collisionEnter(); // for crashing

	void collisionExit(AGameObject* gameObjects);

	void perform();
private:
	bool collided = false;
	bool checked = false;
	sf::FloatRect localBounds;
	CollisionListener* listener;
};