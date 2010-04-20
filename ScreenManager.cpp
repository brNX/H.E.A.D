#include "ScreenManager.h"
#include "Level.h"
#include "Screen.h"

ScreenManager * ScreenManager::lm_instance = 0;


void ScreenManager::start(){
	resources = CL_ResourceManager("resources.xml");
	currentScreen = new Level();
	((Level*) currentScreen)->setupLevel();
}

ScreenManager * ScreenManager::getInstance(){
	if(!lm_instance){
		lm_instance = new ScreenManager;
	}
	return lm_instance;
}

void ScreenManager::drawCurrentScreen(){
	currentScreen->draw();
}


CL_Sprite * ScreenManager::getSprite(CL_String8 name){
	return new CL_Sprite(gc, name, &resources);
}

void ScreenManager::handleEvents(){
	currentScreen->HandleEvents();
}
