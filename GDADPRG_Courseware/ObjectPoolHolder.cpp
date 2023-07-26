
#include "ObjectPoolHolder.h"

string ObjectPoolHolder::ENEMY_A_POOL_TAG = "EnemyPool_A";
string ObjectPoolHolder::ENEMY_B_POOL_TAG = "EnemyPool_B";
string ObjectPoolHolder::ENEMY_C_POOL_TAG = "EnemyPool_C";
string ObjectPoolHolder::ENEMY_D_POOL_TAG = "EnemyPool_Consumable";
string ObjectPoolHolder::ENEMY_E_POOL_TAG = "EnemyPool_E";


ObjectPoolHolder* ObjectPoolHolder::sharedInstance = NULL;

ObjectPoolHolder* ObjectPoolHolder::getInstance()
{
	if (sharedInstance == NULL) {
		sharedInstance = new ObjectPoolHolder();
	}

	return sharedInstance;
}

void ObjectPoolHolder::registerObjectPool(GameObjectPool* pool)
{
	this->poolMap[pool->getTag()] = pool;
}

void ObjectPoolHolder::unregisterObjectPool(GameObjectPool* pool)
{
	this->poolMap.erase(pool->getTag());
	delete pool;
}

GameObjectPool* ObjectPoolHolder::getPool(string tag)
{
	return this->poolMap[tag];
}