#include "EnemySwarmHandler_D.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "BonusCar.h"
#include "GameObjectManager.h"
#include "CarPlayer.h"

EnemySwarmHandler_D::EnemySwarmHandler_D(int numEnemies, string name, int level, float interval) : AComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_D_POOL_TAG, new BonusCar("bonusCar",level), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	this->level = level;
	this->SPAWN_INTERVAL = interval;
}

EnemySwarmHandler_D::~EnemySwarmHandler_D()
{

}

//spawn function
void EnemySwarmHandler_D::perform()
{
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");

	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_D_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	//spawn condition
	if (this->ticks > SPAWN_INTERVAL && player->winCourse == false && player->getDistTrav()>30) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}