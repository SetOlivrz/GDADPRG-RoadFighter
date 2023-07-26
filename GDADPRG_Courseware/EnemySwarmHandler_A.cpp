#include "EnemySwarmHandler_A.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar_A.h"
#include "GameObjectManager.h"
#include "CarPlayer.h"

EnemySwarmHandler_A::EnemySwarmHandler_A(int numEnemies, string name, int level, float interval) : AComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_A_POOL_TAG, new EnemyCar_A("enemy",level), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	this->level = level;
	this->SPAWN_INTERVAL = interval;
}

EnemySwarmHandler_A::~EnemySwarmHandler_A()
{

}

//spawn function
void EnemySwarmHandler_A::perform()
{
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");

	
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_A_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	//spawn condition
	if (this->ticks > SPAWN_INTERVAL && player->winCourse == false) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}