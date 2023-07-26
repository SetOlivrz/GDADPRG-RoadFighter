#include "GameOverScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "PhysicsManager.h"

GameOverScreen::GameOverScreen(string name):AGameObject(name)
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::initialize()
{
}

void GameOverScreen::onButtonClick(UIButton* button)
{
}

void GameOverScreen::onButtonReleased(UIButton* button)
{
}

void GameOverScreen::markMainMenuQuit()
{
}

void GameOverScreen::markGameQuit()
{
}
