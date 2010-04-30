#include "ScreenManager.h"
#include "Level.h"
#include "Screen.h"

ScreenManager * ScreenManager::lm_instance = 0;


///inicia os objectos 
void ScreenManager::start(){
	resources = CL_ResourceManager("resources.xml");
	wiimote = new Wiimote_handler();
	wiimote->init();
	
	//todo: por enquanto so 1 nivel , depois fazer um loader (p.ex de um ficheiro xml ou json)
	currentScreen = new Level();
	((Level*) currentScreen)->setupLevel();
	currentScreenType = S_PLAYING;
}

ScreenManager * ScreenManager::getInstance(){
	if(!lm_instance){
		lm_instance = new ScreenManager;
	}
	return lm_instance;
}

///desenha o screen actual (level e/ou menu)
void ScreenManager::drawCurrentScreen(){

	currentScreen->draw();

	switch (currentScreenType){
	case S_WIN:drawWin(); break;//TODO: mandar sinal , ou esperar por teclado para abrir menu
	case S_MENU: break;
	case S_PLAYING:break;
	case S_OVER: drawLose();break;
	}
}

///devolve CL_Sprite utilizando o resourcemanager
CL_Sprite * ScreenManager::getSprite(CL_String8 name){
	return new CL_Sprite(gc, name, &resources);
}

///proximo passo da logica e I/O
void ScreenManager::handleEvents(){
	wiimote->poll();
	currentScreen->wiimote_input(wiimote->getPitch());
	currentScreen->HandleEvents();
}

/// A key was pressed
void ScreenManager::on_input_down(const CL_InputEvent &key, const CL_InputState &state)
{
	currentScreen->on_input_down(key,state);
}