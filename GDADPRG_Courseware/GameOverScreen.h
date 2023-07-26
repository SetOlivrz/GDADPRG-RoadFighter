#pragma once
#include "UIButtonInputController.h"
class GameOverScreen: public AGameObject, public ButtonListener
{
public:
	GameOverScreen(string name);
	~GameOverScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

	void markMainMenuQuit();
	void markGameQuit();

private:
	bool forMainMenu = false;

};
