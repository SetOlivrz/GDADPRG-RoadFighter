#pragma once
#include "AComponent.h"
class HUDUpdate :public AComponent
{
public:
	HUDUpdate(string name);
	void perform();
};

