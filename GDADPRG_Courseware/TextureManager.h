#pragma once
#include <SFML/Graphics.hpp>;
#include <unordered_map>

class TextureManager
{
    public:
        static TextureManager* getInstance();
        void testFunction();

        void loadAll();
        sf::Texture* getTexture(std::string);
        void getFrame(std::string key, sf::Sprite* s);

    private:
        // set constructor to private
        TextureManager() {}; 
        // set copy contructor to private
        TextureManager(TextureManager const&) {};
        // assignment operator is private
        TextureManager& operator=(TextureManager const&){}; 
        static TextureManager* sharedInstance;

        void loadTexture(std::string,std::string);
        std::unordered_map<std::string, sf::Texture*> textureMap;
        std::unordered_map<std::string, std::string> stringMap;

};