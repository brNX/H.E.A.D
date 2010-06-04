#pragma once
#include "Screen.h"
#include <vector>
#include <Box2D/Box2D.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "BallContactListener.h"
#include "PhysicalObject.h"

class Ball;

class Level :
	public Screen
{
public:
	Level(CL_String _name,int levelindex);
	~Level(void);
	void setupLevel();
	void draw();
	void HandleEvents();
	void on_input_down(const CL_InputEvent &key, const CL_InputState &state);
	void wiimote_input(float pitch);
	inline b2World * getWorld(){return world;}
	inline CL_String getName(){return name;}
	inline void setName(CL_String _name){name=_name;}
private:
	CL_String name;
	Ball * gameBall;
	int levelindex;
	//PhysicalObject * currentControllableObject;
	std::vector<PhysicalObject*> controllableObjects;
	std::vector<PhysicalObject*> levelitems;
	b2World * world;
	BallContactListener listener;
	void restart();

	std::map<CL_String,EObjectType> dict;
};
