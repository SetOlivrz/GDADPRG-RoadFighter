#include "AirplanePlayer.h"
#include <iostream>
#include "Game.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "RendererFactory.h"
#include "DebugRendererFactory.h"

AirplanePlayer::AirplanePlayer(string name) : AGameObject(name) {

}

void AirplanePlayer::initialize() {
	std::cout << "Declared as " << this->getName() << "\n";

    this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

    PlayerInputController* inputController = new PlayerInputController("MyPlayerInput");
    this->attachComponent(inputController);

    PlayerMovement* movement = new PlayerMovement("MyMovement");
    this->attachComponent(movement);

    // Renderer* renderer = Renderer::Create("AirplanePlayerRenderer", "eagle", RendererType::Sprite);
    ARendererFactory* factory = new RendererFactory();
    Renderer* renderer = factory->createSprite("AirplanePlayerRenderer", "eagle");
    this->attachComponent(renderer);
}