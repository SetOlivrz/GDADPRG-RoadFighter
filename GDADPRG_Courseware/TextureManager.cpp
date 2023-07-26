#include <stddef.h>
#include <iostream>
#include "TextureManager.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance() {
		//initialize only when we need it
		if (sharedInstance == NULL) {
			sharedInstance = new TextureManager();
		}
		return sharedInstance;
}

void TextureManager::loadAll() 
{
	loadTexture("btn_normal", "Media/Textures/idle.png");
	loadTexture("btn_pressed", "Media/Textures/pressed.png");

	loadTexture("black_bg", "Media/Textures/black_bg.png");
	loadTexture("hud_bg", "Media/Textures/hud_bg.png");

	// courses
	loadTexture("course_1_bg", "Media/Textures/course_1.png");
	loadTexture("course_1.2_bg", "Media/Textures/course_1.2.png");
	loadTexture("course_1.3_bg", "Media/Textures/course_1.3.png");
	loadTexture("course_1.4_bg", "Media/Textures/course_1.4.png");
	loadTexture("course_2_bg", "Media/Textures/course_2.png");
	loadTexture("course_3_bg", "Media/Textures/course_3.png");


	loadTexture("finish_1_bg", "Media/Textures/finish_1.png");
	loadTexture("finish_2_bg", "Media/Textures/finish_2.png");
	loadTexture("finish_3_bg", "Media/Textures/finish_3.png");

	// side icons
	loadTexture("sidemap_1", "Media/Textures/sidemap_1.png");
	loadTexture("sidemap_2", "Media/Textures/sidemap_2.png");
	loadTexture("sidemap_3", "Media/Textures/sidemap_3.png");

	// sprite sheet
	loadTexture("roadfighter", "Media/Textures/SpriteSheets/roadfighter.png");

	
	// string map for 
	stringMap["title_bg"] = "title.png";
	stringMap["title_bg"] = "title.png";
	stringMap["black_bg"] = "black_bg.png";

	stringMap["player_icon"] = "icon1.png";


	// CARS
	stringMap["player"] = "p1.png";
	stringMap["skidLeft"] = "p2.png";
	stringMap["skidRight"] = "p5.png";

	stringMap["enemy_car1"] = "c1.png";
	stringMap["enemy_car2"] = "c7.png";
	stringMap["enemy_car3"] = "c12.png";
	stringMap["bonus_car"] = "icon2.png";
	stringMap["truck"] = "truck.png";

	// EFFECTS
	stringMap["crash1"] = "crash1.png";
	stringMap["crash2"] = "crash2.png";
	stringMap["crash3"] = "crash3.png";

	//Main menu bg
	stringMap["title"] = "Media/Textures/title.png";


	loadTexture("player_icon", "Media/Textures/icon1.png");


}

void TextureManager::loadTexture(std::string key, std::string path) {
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	textureMap[key] = texture;
}

sf::Texture* TextureManager::getTexture(std::string key) {
	if (textureMap[key] != NULL) {
		return textureMap[key];
	}
	else {
		std::cout << "No texture found for " << key;
		return NULL;
	}
}

void TextureManager::testFunction() {
	std::cout << "Hi, I'm single-ton ;D";
}

void TextureManager::getFrame(std::string keys, sf::Sprite* sprite)
{

	sprite->setTexture(*getTexture("roadfighter"));
	// access the json file
	FILE* file = new FILE();
	fopen_s(&file, "Media/Textures/SpriteSheets/roadfighter.json", "rb"); // open json file
	char readBuffer[15000];

	assert(file != 0);

	rapidjson::FileReadStream is(file, readBuffer, sizeof(readBuffer));
	rapidjson::Document doc;

	doc.ParseStream(is);
	fclose(file);

	rapidjson::Value& frames = doc["frames"]; // doc file is "frames"
	std::string key = stringMap[keys]; // name of the png name
	const char* textureCode = key.c_str();



	sf::IntRect rec(
		// doc file [png name]["axis"]
		frames[textureCode]["frame"]["x"].GetInt(),
		frames[textureCode]["frame"]["y"].GetInt(),
		frames[textureCode]["frame"]["w"].GetInt(),
		frames[textureCode]["frame"]["h"].GetInt()
	);
	sprite->setTextureRect(rec);
}