#pragma once
#include "AComponent.h"

enum class RendererType { Custom, Sprite};
class Renderer : public AComponent
{
public:
	
	Renderer(string name);
	virtual ~Renderer();
	void assignTargetWindow(sf::RenderWindow* window);
	void assignDrawable(sf::Drawable* drawable);
	void setRenderStates(sf::RenderStates renderStates);

	void perform();

	static Renderer* Create(string name, string type, string resourcesName, sf::Sprite* sprite,  RendererType rendererType);
	static Renderer* CreateSprite(string name, string type, string resourceName, sf::Sprite* sprite);

protected:
	//used to be private, now we moved to protected since we're extending
	sf::Drawable* drawable = NULL;
private:
	sf::RenderWindow* targetWindow = NULL;
	
	sf::RenderStates renderStates = sf::RenderStates::Default;
};


