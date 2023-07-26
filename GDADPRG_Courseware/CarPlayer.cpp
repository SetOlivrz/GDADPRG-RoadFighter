#include "CarPlayer.h"
#include <iostream>
#include "Game.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"
#include "Collider.h"
#include "Bounds.h"
#include "PhysicsManager.h"
#include "ScoreManager.h"
#include "PlayerAudioHandler.h"

CarPlayer::CarPlayer(string name, int level):ACar(), AGameObject(name, level), CollisionListener()
{
    
}

void CarPlayer::initialize()
{
    setBounds(level);


    // //assign texture
    sprite = new sf::Sprite();
    ARendererFactory* factory = new RendererFactory();
     renderer = factory->createSprite("CarPlayerRenderer","spritesheet", "player", sprite);
    this->transformable.setScale(.4, .4);
    this->attachComponent(renderer);
  
    // center pos based on BG
    switch(level)
    {
        case 1:this->transformable.setPosition(center, Game::WINDOW_HEIGHT - 100); break;
        case 2:this->transformable.setPosition(center, Game::WINDOW_HEIGHT - 100); break;
        case 3:this->transformable.setPosition(center, Game::WINDOW_HEIGHT - 100); break;
    }
    
    // input comp
    PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
    this->attachComponent(inputController);

    // movement comp
    PlayerMovement* movement = new PlayerMovement("MyMovement");
    this->attachComponent(movement);

    // collider comp (collison)
    Collider* collider = new Collider("PlayerCollider");
    collider->setLocalBounds(this->getGlobalBounds());
    collider->setCollisionListener(this);
    this->attachComponent(collider);
    PhysicsManager::getInstance()->trackObject(collider);

    // bounds comp(score manager)
    Bounds* bounds = new Bounds("PlayerBounds");
    bounds->setLocalBounds(this->getGlobalBounds());
    this->attachComponent(bounds);
    ScoreManager::getInstance()->trackObject(bounds);

    // audio handler comp
    PlayerAudioHandler* audioHandler = new PlayerAudioHandler("PlayerAudioHandler");
    this->attachComponent(audioHandler);
    cout <<"Positions::   "<< sprite->getPosition().x <<" "<< sprite->getPosition().y << "\n";
    //system("pause");
}

void CarPlayer::nonColliding()
{
    
}

// collision with bonus car
void CarPlayer::colliding(AGameObject* object)
{
    addFuel(10);
}

// collision skidding
void CarPlayer::colliding(int dir)
{
    this->skidding = true;
    this->direction = dir;
}

void CarPlayer::collidingObstacle()
{
    this->crash(true);
}

// setter for crashed attr
void CarPlayer::crash(bool flag)
{
    
    this->crashed = flag;
   
    if (crashed == true)
    {
        this->SPEED_MULTIPLIER = 0;
    }
}

// getter for player speed
float CarPlayer::getSpeed()
{
    return  this->SPEED_MULTIPLIER;
}

// getter for player fuel
float CarPlayer::getFuel()
{
    return this->fuel;
}

// getter for distance travelled
float CarPlayer::getDistTrav()
{
    return (this->disTravelled) / 1000.f;
}

// setter for player fuel
void CarPlayer::setFuel(float fuel)
{
    this->fuel = fuel;
}

// setter fir speed
void CarPlayer::setSpeed(float spd)
{
    SPEED_MULTIPLIER = spd;
}

// setter for dist travelled
void CarPlayer::addDistTrav(float dist)
{
    this->disTravelled += dist;
}

// update fuel
void CarPlayer::updateFuel(float gas)
{
    this->fuel -= gas;
}

// add passed parameter to fuel
void CarPlayer::addFuel(float gas)
{
    this->fuel += gas;
}

