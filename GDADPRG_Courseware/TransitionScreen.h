#pragma once
#include "UIButtonInputController.h"
class TransitionScreen : public AGameObject, public ButtonListener
{
public:
	TransitionScreen(string name, int level);
	~TransitionScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

	void markRestartPrevScene();
	void markNextGameScene();

};

