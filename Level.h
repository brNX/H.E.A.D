#pragma once
#include "Screen.h"
#include <vector>
#include <Box2D/Box2D.h>
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
	inline b2World * getWorld(){return world;} 
private:
	Ball * gameBall;
	std::vector<PhysicalObject*> levelitems;
	b2World * world;
	BallContactListener listener;
};
