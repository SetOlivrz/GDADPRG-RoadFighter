#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>
#include <iostream>

using namespace std;

class AudioManager
{
public:
        static AudioManager* getInstance();
        void testFunction();

        void loadAll();
        sf::Sound* getSound(string key);
        void playSoundOnce(string key);
        void playSoundInLoop(string key);

        void stopSound(string key);
        void stopAllSounds();

        void pauseSound(string key);
        void pauseAllSounds();
        void unpauseAllSounds();
        bool isPlaying(string key);
private:
        // set constructor to private
        AudioManager() {}; 
        // set copy contructor to private
        AudioManager(AudioManager const&) {};
        // assignment operator is private
        AudioManager& operator=(AudioManager const&){}; 
        static AudioManager* sharedInstance;

        void loadSound(string,string);
        //sf::Sound* sound;
        std::unordered_map<std::string, sf::Sound*> SoundMap;
        vector<string>AudioFileNames;
};

