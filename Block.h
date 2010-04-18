#pragma once
#include "PhysicalObject.h"

class Block :
	public PhysicalObject
{
public:
	Block(void);
	Block(float hsizex,float hsizey,float x, float y);
	~Block(void);
private:
	float hsizeX;
	float hsizeY;
public:
	void draw();
	void handleevents();
	void setHsize(float sizex,float sizey);
};
