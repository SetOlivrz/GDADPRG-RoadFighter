#include "EnemySwarmHandler_E.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyTruck.h"
#include "GameObjectManager.h"
#include "CarPlayer.h"

EnemySwarmHandler_E::EnemySwarmHandler_E(int numEnemies, string name, int level, float interval) : AComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_E_POOL_TAG, new EnemyTruck("truck",level), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	this->level = level;
	this->SPAWN_INTERVAL = interval;
}

EnemySwarmHandler_E::~EnemySwarmHandler_E()
{

}

//spawn function
void EnemySwarmHandler_E::perform()
{
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");

	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_E_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	//spawn condition
	if (this->ticks > SPAWN_INTERVAL && player->winCourse == false && player->getDistTrav()>= 40) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}