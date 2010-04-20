#include "LevelManager.h"
#include "Level.h"
#include "Screen.h"

LevelManager * LevelManager::lm_instance = 0;


void LevelManager::start(){
	resources = CL_ResourceManager("resources.xml");
	currentScreen = new Level();
	((Level*) currentScreen)->setupLevel();
}

LevelManager * LevelManager::getInstance(){
	if(!lm_instance){
		lm_instance = new LevelManager;
	}
	return lm_instance;
}

void LevelManager::drawCurrentScreen(){
	currentScreen->draw();
}


CL_Sprite * LevelManager::getSprite(CL_String8 name){
	return new CL_Sprite(gc, name, &resources);
}

void LevelManager::handleEvents(){
	currentScreen->HandleEvents();
}