
#include "Renderer.h"
#include "SpriteRenderer.h"

Renderer::Renderer(string name) : AComponent(name, AComponent::Renderer)
{
	this->type = AComponent::Renderer;
	this->renderStates = sf::RenderStates::Default;
}

Renderer::~Renderer()
{
	delete this->drawable;
}

void Renderer::assignTargetWindow(sf::RenderWindow* window)
{
	this->targetWindow = window;
}

void Renderer::assignDrawable(sf::Drawable* drawable)
{
	this->drawable = drawable;
}

void Renderer::setRenderStates(sf::RenderStates renderStates)
{
	this->renderStates = renderStates;
}

void Renderer::perform() {
	this->targetWindow->draw(*this->drawable, this->renderStates);
}

Renderer* Renderer::Create(string name,string type, string resourceName, sf::Sprite* sprite, RendererType rendererType) {
	switch (rendererType) {
		case RendererType::Sprite:
				return new SpriteRenderer(name,type, resourceName, sprite);
				break;
		case RendererType::Custom:
		default: 
			return new Renderer(name);
	}
}

Renderer* Renderer::CreateSprite(string name, string type,string resourceName, sf::Sprite* sprite) {
	return Renderer::Create(name, type, resourceName, sprite, RendererType::Sprite);
}

