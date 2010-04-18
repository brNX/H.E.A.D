#include "LevelManager.h"

LevelManager * LevelManager::lm_instance = 0;

LevelManager * LevelManager::getInstance(){
	if(!lm_instance)
		lm_instance = new LevelManager;
	return lm_instance;
}
