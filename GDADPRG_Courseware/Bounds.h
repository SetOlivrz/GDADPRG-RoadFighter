#pragma once
#include "AComponent.h"
#include "BoundsListener.h"
class Bounds : public AComponent
{
public:
	Bounds(string name);

	void setBoundsListener(BoundsListener* listener);

	void setChecked(bool flag);
	bool isChecked();

	bool willOvertake(Bounds* another);
	bool alreadyOvertaken();
	void setAlreadyOvertaken(bool flag);

	sf::FloatRect getGlobalBounds();
	void setLocalBounds(sf::FloatRect localBounds);

	void perform();
private:
	bool overtaken = false;
	bool checked = false;
	sf::FloatRect localBounds;
	BoundsListener* listener;
};