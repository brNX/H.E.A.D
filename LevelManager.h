#pragma once
#include <ClanLib/Core.h>
#include <ClanLib/Display.h>

class Screen;


class LevelManager
{
public:
	static LevelManager * getInstance();
	void drawCurrentScreen();
	CL_Sprite * getSprite(CL_String8 name);
private:
	int counter;
	LevelManager();
	static LevelManager * lm_instance;
	Screen * currentScreen;
	CL_ResourceManager * resources;
	CL_GraphicContext * gc;
public:
	inline void setGraphicContext(CL_GraphicContext * gcontext){gc=gcontext;}
	inline Screen * getCurrentScreen(){return currentScreen;}
	inline CL_ResourceManager * getResourceManager(){return resources;}

};
