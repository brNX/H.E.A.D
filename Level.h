#pragma once
#include "Screen.h"
#include <vector>
#include <Box2D/Box2D.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "BallContactListener.h"

class Ball;
class PhysicalObject;

class Level :
	public Screen
{
public:
	Level(void);
	~Level(void);
	void setupLevel();
	void draw();
	void HandleEvents();
	void on_input_down(const CL_InputEvent &key, const CL_InputState &state);
	void wiimote_input(float pitch,bool one , bool two);
	inline b2World * getWorld(){return world;}
private:
	Ball * gameBall;
	int levelindex;
	PhysicalObject * currentControllableObject;
	std::vector<PhysicalObject*> levelitems;
	b2World * world;
	BallContactListener listener;
	void restart();
};
