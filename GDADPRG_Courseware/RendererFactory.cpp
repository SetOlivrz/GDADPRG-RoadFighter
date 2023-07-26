
#include "RendererFactory.h"
#include "SpriteRenderer.h"

Renderer* RendererFactory::createSprite(string name, string type ,string resourceName, sf::Sprite* sprite) 
{
	return SpriteRenderer::CreateSprite(name, type, resourceName, sprite);
}

Renderer* RendererFactory::createCircle(string name, float radius) {
	Renderer* renderer = new Renderer(name);
	sf::CircleShape* drawable = new sf::CircleShape(radius);
	drawable->setOrigin(radius, radius);
	renderer->assignDrawable(drawable);
	return renderer;
}