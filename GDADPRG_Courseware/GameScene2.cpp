#include "GameScene2.h"
#include "BGObject.h"
#include "CarPlayer.h"
#include "EnemyCar_A.h"
#include "EnemyCar_B.h"
#include "EnemyCar_C.h"
#include "GameObjectPool.h"
#include "ObjectPoolHolder.h"
#include "EmptyGameObject.h"
#include "EnemySwarmHandler_A.h"
#include "EnemySwarmHandler_B.h"
#include "EnemySwarmHandler_C.h"
#include "EnemySwarmHandler_D.h"
#include "EnemySwarmHandler_E.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "SceneManager.h"

#include "HUDScreen.h"

GameScene2::GameScene2() :AScene("GameScene2")
{

}

GameScene2::~GameScene2()
{
}

void GameScene2::onLoadResources()
{
}

void GameScene2::onLoadObjects()
{
    unsigned int level = 2;


    BGObject* bgObject = new BGObject("BGObject", level);
   this->registerObject(bgObject);

   CarPlayer* carObject = new CarPlayer("PlayerObject", level);
   this->registerObject(carObject);

    HUDScreen* hudScreen = new HUDScreen("HUDScreen", level);
    this->registerObject(hudScreen);

    //create N enemies via object pooling
    srand(time(NULL));
    EmptyGameObject* enemiesManager = new EmptyGameObject("EnemiesManager", level);
    this->registerObject(enemiesManager);


    EnemySwarmHandler_A* swarmHandler_a = new EnemySwarmHandler_A(3, "SwarmHandler_A", level, 1.35f);
    enemiesManager->attachComponent(swarmHandler_a);

    EnemySwarmHandler_B* swarmHandler_b = new EnemySwarmHandler_B(2, "SwarmHandler_B", level, 8.0f);
    enemiesManager->attachComponent(swarmHandler_b);

    EnemySwarmHandler_C* swarmHandler_c = new EnemySwarmHandler_C(2, "SwarmHandler_C", level, 15.0f);
    enemiesManager->attachComponent(swarmHandler_c);

    EnemySwarmHandler_D* swarmHandler_d = new EnemySwarmHandler_D(1, "SwarmHandler_D", level, 30.0f);
    enemiesManager->attachComponent(swarmHandler_d);

    EnemySwarmHandler_E* swarmHandler_e = new EnemySwarmHandler_E(2, "SwarmHandler_D", level, 30.0f);
    enemiesManager->attachComponent(swarmHandler_e);
}

void GameScene2::onUnloadObjects()
{
    PhysicsManager::getInstance()->destroy();// share = NULL
    ScoreManager::getInstance()->~ScoreManager();

	GameObjectPool* enemyPool_a = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_A_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool_a);

    GameObjectPool* enemyPool_b = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_B_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool_b);

    GameObjectPool* enemyPool_c = ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_C_POOL_TAG);
	ObjectPoolHolder::getInstance()->unregisterObjectPool(enemyPool_c);

	AScene::onUnloadObjects();
}


void GameScene2::onUnloadResources()
{
    
}