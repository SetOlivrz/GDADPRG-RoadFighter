#include "SpriteRenderer.h"
#include "TextureManager.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(string name,string type, string textureName, sf::Sprite* sprite) : Renderer(name) 
{
	//if texture comes from sprite sheet
	if (type == "spritesheet")
	{
		TextureManager::getInstance()->getFrame(textureName, sprite);
		sprite->setOrigin(sprite->getTextureRect().width / 2.f, sprite->getTextureRect().height / 2.f); // set origin to center
		this->assignDrawable(sprite);
	}
	//if texture doesnt come from sprit esheet
	else if(type == "texture")
	{
		sprite->setTexture(*TextureManager::getInstance()->getTexture(textureName));
		sf::Vector2u textureSize = sprite->getTexture()->getSize();
		sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
		this->assignDrawable(sprite);
	}

	//texture doesnt exist
	else
	{
		std::cout << "typo\n\n";
	}

}
