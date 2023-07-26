#include "GameObjectPool.h"
#include <iostream>
#include "GameObjectManager.h"
#include "Collider.h"
#include "Bounds.h"
#include "ScoreManager.h"

#include "PhysicsManager.h"

GameObjectPool::GameObjectPool(string tag, APoolable* poolableCopy, int poolableSize, AGameObject* parent)
{
	this->tag = tag;
	this->objectCopy = poolableCopy;
	this->maxPoolSize = poolableSize;
	this->parent = parent;
}

GameObjectPool::~GameObjectPool()
{
	this->objectCopy = NULL;
	this->parent = NULL;
}
//initializes the object pool
void GameObjectPool::initialize()
{
	for (int i = 0; i < this->maxPoolSize; i++) {
		APoolable* poolableObject = this->objectCopy->clone();
		//instantiate object but disable it.
		if (this->parent != NULL) {
			this->parent->attachChild(poolableObject);
		}
		else {
			GameObjectManager::getInstance()->addObject(poolableObject);
		}
		poolableObject->setEnabled(false);
		this->availableObjects.push_back(poolableObject);
	}
}

bool GameObjectPool::hasObjectAvailable(int requestSize)
{
	return requestSize <= this->availableObjects.size();
}

APoolable* GameObjectPool::requestPoolable()
{
	Collider* collider = NULL;
	Bounds* bounds = NULL;

	if (this->hasObjectAvailable(1)) {
		APoolable* poolableObject = this->availableObjects[this->availableObjects.size() - 1];
		this->availableObjects.erase(this->availableObjects.begin() + this->availableObjects.size() - 1);
		this->usedObjects.push_back(poolableObject);

		std::cout << "Requested object. Available: " << this->availableObjects.size() << " Used: " << this->usedObjects.size() << "\n";
		this->setEnabled(poolableObject, true);

		// gets collider and bounds component
		if(poolableObject->getName() == "enemy")
		{
			collider = (Collider*)poolableObject->findComponentByName("EnemyCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("EnemyBounds");
		}
		else if (poolableObject->getName() == "bonusCar")
		{
			collider = (Collider*)poolableObject->findComponentByName("bonusCarCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("bonusCarCollider");
		}
		else if (poolableObject->getName() == "truck")
		{
			collider = (Collider*)poolableObject->findComponentByName("TruckCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("TruckBounds");
		}
			
		// tracks the objects
		if (collider != NULL)
			PhysicsManager::getInstance()->trackObject(collider);

		if (bounds != NULL)
			ScoreManager::getInstance()->trackObject(bounds);

		return poolableObject;
	}

	else {
		std::cout << " No more poolable " + this->objectCopy->getName() + " available! \n";
		return NULL;
	}
}

ObjectList GameObjectPool::requestPoolableBatch(int size)
{
	ObjectList returnList;
	if (this->hasObjectAvailable(size)) {
		for (int i = 0; i < size; i++) {
			returnList.push_back(this->requestPoolable());
		}
	}
	else {
		std::cout << "Insufficient " + this->objectCopy->getName() + " available in pool. Count is: " << this->availableObjects.size() <<
			" while requested is " << size << "!\n";
	}

	return returnList;
}

void GameObjectPool::releasePoolable(APoolable* poolableObject)
{
	Collider* collider = NULL;
	Bounds* bounds = NULL;
	//find object in used
	int index = -1;
	for (int i = 0; i < this->usedObjects.size(); i++) {
		if (this->usedObjects[i] == poolableObject) {
			index = i;
			break;
		}
	}

	//std::cout << "Poolable index in used: " << index << "\n";
	if (index > -1) {
		this->usedObjects.erase(this->usedObjects.begin() + index);
		this->availableObjects.push_back(poolableObject);
		this->setEnabled(poolableObject, false);

		// gets the collider and bounds
		if (poolableObject->getName() == "enemy")
		{
			collider = (Collider*)poolableObject->findComponentByName("EnemyCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("EnemyBounds");
		}
		else if (poolableObject->getName() == "bonusCar")
		{
			collider = (Collider*)poolableObject->findComponentByName("bonusCarCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("bonusCarCollider");
		}
		else if (poolableObject->getName() == "truck")
		{
			collider = (Collider*)poolableObject->findComponentByName("bonusCarCollider");
			bounds = (Bounds*)poolableObject->findComponentByName("bonusCarCollider");
		}
		
		// untracks the object
		if (collider != NULL)
			PhysicsManager::getInstance()->untrackObject(collider);

		if (bounds != NULL)
			ScoreManager::getInstance()->untrackObject(bounds);
	}

}

void GameObjectPool::releasePoolableBatch(ObjectList objectList)
{
	for (int i = 0; i < objectList.size(); i++) {
		this->releasePoolable(objectList[i]);
	}
}

string GameObjectPool::getTag()
{
	return this->tag;
}

void GameObjectPool::setEnabled(APoolable* poolableObject, bool flag)
{
	if (flag) {
		poolableObject->setEnabled(true);
		poolableObject->onActivate();
	}
	else {
		poolableObject->setEnabled(false);
		poolableObject->onRelease();
	}
}
