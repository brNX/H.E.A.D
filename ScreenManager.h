#pragma once
#include <ClanLib/Core.h>
#include <ClanLib/Display.h>

class Screen;

//TODO: fazer algo quando o tamanho do screen muda (usar slots e signals)

class ScreenManager
{
public:
	static ScreenManager * getInstance();
	void drawCurrentScreen();
	CL_Sprite * getSprite(CL_String8 name);
	void start();
	void handleEvents();
	
	//fun��es inline do draw para ser mais rapido
	inline void drawSprite(CL_Sprite * sprite,float x,float y)
	{
		sprite->draw(gc,x*screenratio,screensizey-(y*screenratio));
	}

	inline void drawBox(float left,float bottom,float right,float top,CL_Colorf& color)
	{
		CL_Draw::box(gc,left*screenratio,screensizey-(bottom*screenratio),right*screenratio,screensizey-(top*screenratio),color);
	}

private:
	
	static ScreenManager * lm_instance;
	
	Screen * currentScreen;

	CL_ResourceManager resources;
	CL_GraphicContext gc;
	CL_DisplayWindow * window;
	
	int screenratio;
	int screensizey;

public:
	inline void setWindow(CL_DisplayWindow * window)
	{
		this->window=window;
		gc=window->get_gc();
		screensizey = window->get_geometry().bottom - window->get_geometry().top;

	}
	
	inline Screen * getCurrentScreen(){return currentScreen;}
	inline void setScreenRatio(int ratio){screenratio=ratio;}
	inline int getScreenRatio(){return screenratio;}

};
