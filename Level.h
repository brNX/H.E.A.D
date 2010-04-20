#pragma once
#include "Screen.h"
#include <Vector>
#include <Box2D/Box2D.h>
#include "BallContactListener.h"

using namespace std;

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
	vector<PhysicalObject*> levelitems;
	b2World * world;
	BallContactListener listener;
};
