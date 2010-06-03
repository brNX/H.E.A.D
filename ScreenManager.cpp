#include "ScreenManager.h"
#include "Level.h"
#include "Screen.h"

ScreenManager * ScreenManager::lm_instance = 0;


///inicia os objectos 
void ScreenManager::start(){
	//sprites
	resources = CL_ResourceManager("resources.xml");

	//init da wiimote
	wiimote = new Wiimote_handler();
	wiimote->init();

	//vai buscar o nome dos niveis ao ficheiro xml
	CL_File file("levels.xml", CL_File::open_existing, CL_File::access_read);
	CL_DomDocument document;
	document.load(file);

	CL_DomNode root = document.get_first_child();
	CL_DomNode current = root.get_first_child();

	printf("niveis?\n");
	while (!current.is_null()){
		const CL_String &level = current.to_element().get_attribute("name");
		printf("%s\n",level.c_str());
		levelnames.push_back(level);
		current=current.get_next_sibling();
	}

	//TODO: menu inicial primeiro
	currentScreen = new Level(levelnames[0],1);
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

	if (currentScreenType != S_RELOADING){
		currentScreen->draw();

		switch (currentScreenType){
			case S_WIN:drawWin(); break;//TODO: mandar sinal , ou esperar por teclado para abrir menu
			case S_MENU: break;
			case S_PLAYING:break;
			case S_OVER: drawLose();break;
		}
	}
}

///devolve CL_Sprite utilizando o resourcemanager
CL_Sprite * ScreenManager::getSprite(CL_String8 name){
	return new CL_Sprite(gc, name, &resources);
}

///proximo passo da logica e I/O
void ScreenManager::handleEvents(){
	wiimote->poll();
	currentScreen->wiimote_input(wiimote->getHead());
	
	if(wiimote->getOne()){
		printf("2\n");
		currentScreenType = S_RELOADING;
		delete currentScreen;
		currentScreen = new Level(levelnames[1],2);
		((Level*) currentScreen)->setupLevel();
		currentScreenType = S_PLAYING;
	}

	if(wiimote->getTwo()){
		printf("1\n");
		currentScreenType = S_RELOADING;
		delete currentScreen;
		currentScreen = new Level(levelnames[0],1);
		((Level*) currentScreen)->setupLevel();
		currentScreenType = S_PLAYING;
	}

	currentScreen->HandleEvents();
}

/// A key was pressed
void ScreenManager::on_input_down(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_2){
		printf("2\n");
		currentScreenType = S_RELOADING;
		delete currentScreen;
		currentScreen = new Level(levelnames[1],2);
		((Level*) currentScreen)->setupLevel();
		currentScreenType = S_PLAYING;

	}else 
		if(key.id == CL_KEY_1){
		printf("1\n");
		currentScreenType = S_RELOADING;
		delete currentScreen;
		currentScreen = new Level(levelnames[0],1);
		((Level*) currentScreen)->setupLevel();
		currentScreenType = S_PLAYING;
		}else 
			currentScreen->on_input_down(key,state);
}
