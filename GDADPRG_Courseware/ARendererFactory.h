#pragma once

#include "Renderer.h"

class ARendererFactory
{
public:
	virtual Renderer* createSprite(string name, string type, string resourceName, sf::Sprite* sprite) = 0;
	virtual Renderer* createCircle(string name, float radius) = 0;
};

