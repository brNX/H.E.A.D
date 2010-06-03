#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <String>
#include "Wiimote_handler.h"


class Screen;

//TODO: fazer algo quando o tamanho do screen muda (usar slots e signals)


enum EScreenType
{
	S_MENU,
	S_PLAYING,
	S_WIN,
	S_OVER,
	S_RELOADING
};

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
		CL_Draw::fill(gc,CL_Rectf(left*screenratio,screensizey-(top*screenratio),right*screenratio,screensizey-(bottom*screenratio)),color);
	}

	
	inline void drawCoutline(CL_CollisionOutline * coutline,float x,float y)
	{
		coutline->draw(0,0,CL_Colorf(0.0f,0.0f,1.0f),gc);
	}


	inline void drawWin()
	{
		CL_Font fnt_clansoft;
		fnt_clansoft = CL_Font(gc, L"Tahoma",120);

		//CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
		fnt_clansoft.draw_text(gc, 300, screensizey/2, "You Win!");
	}

	inline void drawLose()
	{
		CL_Font fnt_clansoft;
		fnt_clansoft = CL_Font(gc, L"Tahoma",120);

		//CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
		fnt_clansoft.draw_text(gc, 300, screensizey/2, "Game over");
	}


private:
	
	static ScreenManager * lm_instance;
	
	Screen * currentScreen;
	EScreenType currentScreenType;

	CL_ResourceManager resources;
	CL_GraphicContext gc;
	CL_DisplayWindow * window;
	
	float screenratio;
	int screensizey;

	Wiimote_handler * wiimote;

	std::vector<CL_String> levelnames;


public:
	inline void setWindow(CL_DisplayWindow * window)
	{
		this->window=window;
		gc=window->get_gc();
		screensizey = window->get_geometry().bottom - window->get_geometry().top-40;
	}

	inline CL_DisplayWindow * getWindow(){return window;}
	
	inline Screen * getCurrentScreen(){return currentScreen;}
	inline void setScreenRatio(float ratio){screenratio=ratio;}
	inline float getScreenRatio(){return screenratio;}
	inline int getScreensizey(){return screensizey;}
	inline void setScreenType(EScreenType type){currentScreenType = type;}
	inline EScreenType getScreenType(){return currentScreenType;}

	void on_input_down(const CL_InputEvent &key, const CL_InputState &state);

	inline void releaseWiimote(){wiimote->release();}

};
