#pragma once
#include "AGameObject.h"
#include "UIButtonInputController.h"
#include "UIText.h"

class HUDScreen : public AGameObject, public ButtonListener
{
public:
	HUDScreen(string name, int level);
	~HUDScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	void setScoreDisp(float scr);
	void setFuelDisp(float gas);
	void setSpeedDisp(float spd);
	void setIconPos(float dis);
	float getIconPos();

private:
	UIText* speedText;
	UIText* fuelText;
	UIText* scoreText;
	sf::Sprite* sprite_main;
	sf::Sprite* sprite_sidemap;
	sf::Sprite* sprite_playerIcon;

	string score = "None";
	string fuel = "None";
	string distance = "None";
	string speed = "None";
	sf::Vector2f iconPos = sf::Vector2f(0,0);



};

