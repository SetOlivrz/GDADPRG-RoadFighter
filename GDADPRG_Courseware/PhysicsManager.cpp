#include "PhysicsManager.h"
#include "CarPlayer.h"
#include <iostream>
#include "ScoreManager.h"
#include"AudioManager.h"

PhysicsManager* PhysicsManager::sharedInstance = NULL;
void PhysicsManager::initialize(string name, AGameObject* parent)
{
    
}

void PhysicsManager::destroy()
{
    sharedInstance = NULL;
}

PhysicsManager* PhysicsManager::getInstance()
{
    if(sharedInstance == NULL)
    {
        sharedInstance = new PhysicsManager("PhysicsManager");
    }

    return sharedInstance;
}

PhysicsManager::~PhysicsManager()
{
    playerCollider = NULL;
    trackedObjects.clear();
}

void PhysicsManager::trackObject(Collider* object)
{
    //cout << object->getName() << endl;
    object->setAlreadyCollided(false);
    trackedObjects.push_back(object);  
}

void PhysicsManager::untrackObject(Collider* object)
{
    if(object->getName() == "PlayerCollider")
    {
        playerCollider = NULL;
    }

    else
    {
        for(unsigned int i = 0; i < trackedObjects.size(); i++)
        {
            if(trackedObjects[i] == object)
            {
                trackedObjects.erase(trackedObjects.begin() + i);
                break;
            }
        }
    }
}

void PhysicsManager::perform()
{
    
    if(playerCollider!=NULL && playerCollider->getOwner() != NULL)
        playerCollider->setLocalBounds(playerCollider->getOwner()->getGlobalBounds()); // update player collider bounds

    // loop through all tracked objects
    for (unsigned int i = 0; i < trackedObjects.size(); i++)
    {
        trackedObjects[i]->setLocalBounds(trackedObjects[i]->getOwner()->getGlobalBounds()); // update enemy collider bounds
        for (int j = 0; j < trackedObjects.size(); j++)
        {
            trackedObjects[j]->setLocalBounds(trackedObjects[j]->getOwner()->getGlobalBounds()); // update enemy collider bounds

            // any possible collisions
            if (trackedObjects[i] != trackedObjects[j] && trackedObjects[i]->willCollide(trackedObjects[j]))
            {
                // bonus car (release bonus car & player addscore)
                if (trackedObjects[i]->getName() == "PlayerCollider" && trackedObjects[j]->getName() == "bonusCarCollider")
                {
                    trackedObjects[j]->collisionEnter(trackedObjects[j]->getOwner());
                    trackedObjects[i]->collisionEnter(trackedObjects[i]->getOwner());

                    //system("pause");
                }

                // truck (player crash & skid truck)
                else if (trackedObjects[i]->getName() == "PlayerCollider" && trackedObjects[j]->getName() == "TruckCollider")
                {
                    trackedObjects[i]->collisionEnter(); // player
                    trackedObjects[j]->collisionEnter(0);// truck
                }

                // playey to non-player & non-player to non-player (skid)
               else if (trackedObjects[i]->getOwner()->getTransformable()->getPosition().x > trackedObjects[j]->getOwner()->getTransformable()->getPosition().x)
                {
                    // right
                    trackedObjects[i]->collisionEnter(2);
                    trackedObjects[j]->collisionEnter(1);
                }
                else if (trackedObjects[i]->getOwner()->getTransformable()->getPosition().x < trackedObjects[j]->getOwner()->getTransformable()->getPosition().x)
                {
                    // left
                    trackedObjects[i]->collisionEnter(1);
                    trackedObjects[j]->collisionEnter(2);
                }
            }
        }
    }
}

void PhysicsManager::cleanUpObjects()
{
    for (int i = 0; i < forCleaningObjects.size(); i++)
    {
        
    }
    forCleaningObjects.clear();
}
