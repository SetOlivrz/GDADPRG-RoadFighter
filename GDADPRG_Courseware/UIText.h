#pragma once
#include "AGameObject.h"
class UIText :
	public AGameObject
{
public:
	UIText(string name);
	~UIText();
	void initialize();
	void setText(string text);
	string getStringText();
	void setSize(unsigned int size);
	void setColorFill(sf::Color col);
	void setColorOutline(sf::Color col);
	void setColorOutThickness(float thick);
	sf::Text* getText();



private:
	sf::Text* text;
};

