#pragma once
#include "ARendererFactory.h"
class RendererFactory :
    public ARendererFactory
{
public:
	Renderer* createSprite(string name, string type, string resourceName, sf::Sprite* sprite);
	Renderer* createCircle(string name, float radius);
};

