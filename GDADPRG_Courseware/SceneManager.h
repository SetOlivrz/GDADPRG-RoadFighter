
#pragma once
#include <unordered_map>
#include "AScene.h"

typedef std::unordered_map<string, AScene*> SceneTable;
typedef std::vector<string> SceneList;
class SceneManager
{
public:
	//scene names
	static string MAIN_MENU_SCENE_NAME;
	static string GAME_SCENE_NAME;
	static string GAME_SCENE_2_NAME;
	static string GAME_SCENE_3_NAME;

	static SceneManager* getInstance();
	void registerScene(AScene* scene);
	void loadScene(string name); //also calls unload of the previous scene automatically
	void unloadScene();
	bool isSceneLoaded(string name);
	void checkLoadScene();

private:
	SceneManager() {};
	SceneManager(SceneManager const&) {};             // copy constructor is private
	SceneManager& operator=(SceneManager const&) {};  // assignment operator is private
	static SceneManager* sharedInstance;

	SceneTable storedScenes;
	//SceneTable activeScenes;
	AScene* activeScene;
	string toLoadSceneName;
	bool isLoading = false;

};