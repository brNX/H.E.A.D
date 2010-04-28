#pragma once
#include <ClanLib/core.h>
#include <ClanLib/display.h>

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
	
	//funcoes inline do draw para ser mais rapido
	inline void drawSprite(CL_Sprite * sprite,float x,float y)
	{
		sprite->draw(gc,x*screenratio,screensizey-(y*screenratio));
	}

	inline void drawBox(float left,float bottom,float right,float top,CL_Colorf& color)
	{
		CL_Draw::box(gc,left*screenratio,screensizey-(bottom*screenratio),right*screenratio,screensizey-(top*screenratio),color);
	}

	
	inline void drawCoutline(CL_CollisionOutline * coutline,float x,float y)
	{
		coutline->draw(0,0,CL_Colorf(0.0f,0.0f,1.0f),gc);
	}

private:
	
	static ScreenManager * lm_instance;
	
	Screen * currentScreen;

	CL_ResourceManager resources;
	CL_GraphicContext gc;
	CL_DisplayWindow * window;
	
	float screenratio;
	int screensizey;

public:
	inline void setWindow(CL_DisplayWindow * window)
	{
		this->window=window;
		gc=window->get_gc();
		screensizey = window->get_geometry().bottom - window->get_geometry().top;
	}
	
	inline Screen * getCurrentScreen(){return currentScreen;}
	inline void setScreenRatio(float ratio){screenratio=ratio;}
	inline float getScreenRatio(){return screenratio;}
	inline int getScreensizey(){return screensizey;}

};
