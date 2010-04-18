#include "LevelManager.h"
#include "Screen.h"

LevelManager * LevelManager::lm_instance = 0;

LevelManager::LevelManager(){
	counter=0;
	resources = new CL_ResourceManager("resources.xml");
}

LevelManager * LevelManager::getInstance(){
	if(!lm_instance)
		lm_instance = new LevelManager();
	return lm_instance;
}

void LevelManager::drawCurrentScreen(){
	currentScreen->draw();
}


CL_Sprite * LevelManager::getSprite(CL_String8 name){

	return new CL_Sprite(gc, name, resources);
}