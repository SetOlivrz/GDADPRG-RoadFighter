#pragma once
#include "Renderer.h"
class SpriteRenderer :
	public Renderer
{
	public:
		SpriteRenderer(string name,string type, string textureName, sf::Sprite* sprite);
};

