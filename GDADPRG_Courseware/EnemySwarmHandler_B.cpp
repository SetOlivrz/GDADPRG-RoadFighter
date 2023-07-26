#include "EnemySwarmHandler_B.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar_B.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"

EnemySwarmHandler_B::EnemySwarmHandler_B(int numEnemies, string name, int level, float interval) : AComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_B_POOL_TAG, new EnemyCar_B("enemy", level), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	this->level = level;
	this->SPAWN_INTERVAL = interval;
}

EnemySwarmHandler_B::~EnemySwarmHandler_B()
{

}

//spawn function
void EnemySwarmHandler_B::perform()
{
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");

	
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_B_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	//spawn condition
	if (this->ticks > SPAWN_INTERVAL && player->getDistTrav()>=10 && player->winCourse == false) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}