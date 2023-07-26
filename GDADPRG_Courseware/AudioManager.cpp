#include "AudioManager.h"
#include <stddef.h>
#include <iostream>
AudioManager* AudioManager::sharedInstance = NULL;

AudioManager* AudioManager::getInstance() {
		//initialize only when we need it
		if (sharedInstance == NULL) {
			sharedInstance = new AudioManager();
		}
		return sharedInstance;
}

void AudioManager::loadAll() {

	
	// load all the audio files from path
	loadSound("countdown", "Media/Audio/countdown.wav");
	loadSound("max_speed", "Media/Audio/max_speed.wav");
	loadSound("skidding", "Media/Audio/player-skidding.wav");
	loadSound("accelerating", "Media/Audio/acceleration startup.wav");
	loadSound("fuel_warning", "Media/Audio/lowfuel.wav");
	loadSound("headstart", "Media/Audio/Headstart.wav");
	loadSound("goal", "Media/Audio/goal.wav");
	loadSound("collide", "Media/Audio/collide.wav");
	loadSound("crash", "Media/Audio/crash.wav");
	loadSound("bonus_car", "Media/Audio/bonus_car.wav");
}

// load audio and maps it as sound
void AudioManager::loadSound(std::string key, std::string path) {
	sf::SoundBuffer* buffer = new sf::SoundBuffer();
	sf::Sound* sound  = new sf::Sound();

	buffer->loadFromFile(path);
	sound->setBuffer(*buffer);
	SoundMap[key] = sound; // maps file to key
}

//getter for sounds from audio hashtable using key
sf::Sound* AudioManager::getSound(string key) {

	if (SoundMap[key] != NULL) {
		return SoundMap[key];
	}
	else {
		std::cout << "no sound found for " << key;
		return NULL;
	}
}

void AudioManager::testFunction() {
	std::cout << "hi, i'm single-ton ;d";
}

//play hashed sound
void AudioManager::playSoundOnce(string key)
{

	if (SoundMap[key]->getStatus() != sf::Sound::Playing)	//condition to make sure sounds arent forced to restart
	{
		SoundMap[key]->play();
	}

}

//plays a sound in a loop until manually stopped
void AudioManager::playSoundInLoop(std::string key)
{
	if (SoundMap[key]->getStatus() != sf::Sound::Playing)	//condition to make sure sounds arent forced to restart
	{
		SoundMap[key]->setLoop(true);
		SoundMap[key]->play();
	}
}

//stop sound
void AudioManager::stopSound(string key)
{
	if (SoundMap[key]->getStatus() == sf::Sound::Playing)
	{
		SoundMap[key]->stop();
	}
}

//pause sound
void AudioManager::pauseSound(string key)
{
	SoundMap[key]->pause();
}

//check if sound is playing
bool AudioManager::isPlaying(string key)
{
	return (SoundMap[key]->getStatus() == sf::Sound::Playing);
}

//stop all sounds that are playing
void AudioManager::stopAllSounds()
{
	std::unordered_map<std::string, sf::Sound*>::iterator it = SoundMap.begin();
	// Iterate over the map using iterator
	while(it != SoundMap.end())
	{
		it->second->stop();
		it++;
	}

}

//pause all sounds that are playing
void AudioManager::pauseAllSounds()
{
	std::unordered_map<std::string, sf::Sound*>::iterator it = SoundMap.begin();
	// Iterate over the map using iterator
	while(it != SoundMap.end())
	{
		if(it->second->getStatus() == sf::Sound::Playing)
		it->second->pause();
		it++;
		cout << "pause\n\n";
	}

}

//unpause all paused sounds
void AudioManager::unpauseAllSounds()
{
	std::unordered_map<std::string, sf::Sound*>::iterator it = SoundMap.begin();
	// Iterate over the map using iterator
	while(it != SoundMap.end())
	{
		if(it->second->getStatus() == sf::Sound::Paused)
		it->second->play();
		it++;
	}

}