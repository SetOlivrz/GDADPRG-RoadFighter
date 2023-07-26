#pragma once
#include "AComponent.h"
#include "AGameObject.h"
#include <unordered_map>
#include <vector>
#include "Bounds.h"

typedef std::vector<Bounds*> BoundsList;

class ScoreManager: public AComponent
{
public:
	static void initialize(string name, AGameObject* parent);
	static void destroy();
	static ScoreManager* getInstance();
	~ScoreManager();

	void trackObject(Bounds* object);
	void untrackObject(Bounds* object); 
	void perform();

	void updateScore(int addScore);
	int getScore();

private:
	ScoreManager(string name) : AComponent(name, Script) {};
	ScoreManager(ScoreManager const&) : AComponent(name, Script) {};             // copy constructor is private
	ScoreManager& operator=(ScoreManager const&) {};  // assignment operator is private
	static ScoreManager* sharedInstance;

	BoundsList trackedObjects;
	BoundsList forCleaningObjects;
	Bounds* playerBounds;
	void cleanUpObjects();
	int score = 0;
};

