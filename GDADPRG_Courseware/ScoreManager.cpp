#include "ScoreManager.h"
#include "CarPlayer.h"
#include <iostream>

ScoreManager* ScoreManager::sharedInstance = NULL;
void ScoreManager::initialize(string name, AGameObject* parent)
{
    
}

void ScoreManager::destroy()
{
    sharedInstance = NULL;
}

ScoreManager* ScoreManager::getInstance()
{
    if(sharedInstance == NULL)
    {
        sharedInstance = new ScoreManager("ScoreManager");
    }

    return sharedInstance;
}

ScoreManager::~ScoreManager()
{
    cout << "deconstruct scor manager\n";
    int savedScore = 0;
    savedScore = this->score;
    sharedInstance = new ScoreManager("ScoreManager");
    getInstance()->updateScore(savedScore);

}

void ScoreManager::trackObject(Bounds* object)
{
   if(object->getName() == "PlayerBounds")
   {
        playerBounds = object;
   }
   else
   trackedObjects.push_back(object);          
}

void ScoreManager::untrackObject(Bounds* object)
{
    if(object->getName() == "PlayerBounds")
    {
        playerBounds = NULL;
    }

    else
    {
        for(unsigned int j = 0; j < trackedObjects.size(); j++)
        {
            if(trackedObjects[j] == object)
            {
                trackedObjects.erase(trackedObjects.begin() + j);
                break;
            }
        }
    }
}

void ScoreManager::perform()
{
   
    //untrack NULL objects
    for (unsigned int i = 0; i < trackedObjects.size(); i++)
    {
        if (trackedObjects[i]->getOwner() == NULL)
            untrackObject(trackedObjects[i]);
    }

    if (playerBounds != NULL && playerBounds->getOwner() != NULL)
    {
        playerBounds->setLocalBounds(playerBounds->getOwner()->getGlobalBounds()); // update player bounds

        for (unsigned int i = 0; i < trackedObjects.size(); i++)
        {
            trackedObjects[i]->setLocalBounds(trackedObjects[i]->getOwner()->getGlobalBounds()); // update bounds

            if (playerBounds->willOvertake(trackedObjects[i])) // overtake
            {
                forCleaningObjects.push_back(trackedObjects[i]); // add for cleaning
            }
        }
    }
        // update player collider bounds
    cleanUpObjects();
    
}

void ScoreManager::cleanUpObjects()
{
    for (int i = 0; i < forCleaningObjects.size(); i++)
    {
        forCleaningObjects[i]->setAlreadyOvertaken(true);
        untrackObject(forCleaningObjects[i]);
        updateScore(50); // add score

    }
    forCleaningObjects.clear();
}

void ScoreManager::updateScore(int addScore)
{
    this->score += addScore;
}

int ScoreManager::getScore()
{
    return score;
}

