#include "UIText.h"
#include "FontManager.h"
#include "Renderer.h"

UIText::UIText(string name) : AGameObject(name)
{
	this->text = new sf::Text();
}
UIText::~UIText() {
}

void UIText::initialize()
{
	//declare a text to be used
	//font must be a pointer or else it gets immediately de-allocated.
	sf::Font* font = FontManager::getInstance()->getFont("pix");
	text->setFont(*font);
	text->setFillColor(sf::Color::White);
	//text->setOutlineColor(sf::Color::Black);
	text->setOutlineThickness(5.0f);
	this->setSize(40);
	this->setText("<Using placeholder!>");

	Renderer* renderer = new Renderer("Text");
	renderer->assignDrawable(text);
	this->attachComponent(renderer);
}

void UIText::setText(string text) {
	this->text->setString(text);
	sf::FloatRect bounds = this->text->getLocalBounds();
	// Align center, you can put other alignment here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

string UIText::getStringText() {

	return this->text->getString();
}


void UIText::setSize(unsigned int size) {
	this->text->setCharacterSize(size);
}

void UIText::setColorOutline(sf::Color col)
{
}

void UIText::setColorOutThickness(float thick)
{
	text->setOutlineThickness(thick);
}

sf::Text* UIText::getText()
{
	return text;
}

void UIText::setColorFill(sf::Color col)
{
	text->setFillColor(col);
}
