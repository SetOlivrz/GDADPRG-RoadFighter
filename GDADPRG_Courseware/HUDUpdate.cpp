#include "HUDUpdate.h"
#include "HUDScreen.h"
#include "CarPlayer.h"
#include "ScoreManager.h"
#include "GameObjectManager.h"

HUDUpdate::HUDUpdate(string name):AComponent(name, Script)
{
	
}

void HUDUpdate::perform()
{
	
	HUDScreen* HUDmain = (HUDScreen*)this->getOwner();
	CarPlayer* player = (CarPlayer*)GameObjectManager::getInstance()->findObjectByName("PlayerObject");
	int scr = ScoreManager::getInstance()->getScore();

	HUDmain->setFuelDisp(player->getFuel());
	HUDmain->setSpeedDisp(player->getSpeed());
	HUDmain->setIconPos(player->getDistTrav() * 11.16);
	HUDmain->setScoreDisp(scr);
}
