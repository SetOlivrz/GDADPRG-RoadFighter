#include "EnemySwarmHandler_C.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EnemyCar_C.h"
#include "CarPlayer.h"
#include "GameObjectManager.h"

EnemySwarmHandler_C::EnemySwarmHandler_C(int numEnemies, string name, int level, float interval) : AComponent(name, Script)
{
	GameObjectPool* enemyPool = new GameObjectPool(ObjectPoolHolder::ENEMY_C_POOL_TAG, new EnemyCar_C("enemy", level), numEnemies, NULL);
	enemyPool->initialize();
	ObjectPoolHolder::getInstance()->registerObjectPool(enemyPool);
	this->level = level;
	this->SPAWN_INTERVAL = interval;
}

EnemySwarmHandler_C::~EnemySwarmHandler_C()
{

}

//spawn function
void EnemySwarmHandler_C::perform()
{
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");

	
	GameObjectPool* enemyPool = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_C_POOL_TAG);
	this->ticks += this->deltaTime.asSeconds();

	//spawn condition
	if (this->ticks > SPAWN_INTERVAL && player->getDistTrav() >= 25.5f && player->winCourse == false) {
		this->ticks = 0.0f;
		enemyPool->requestPoolable();
	}
}