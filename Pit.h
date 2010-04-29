#pragma once
#include "PhysicalObject.h"

class Pit :
	public PhysicalObject
{
public:
	Pit(void);
	Pit(float hsizex,float hsizey,float x, float y);
	~Pit(void);
private:
	float hsizeX;
	float hsizeY;
public:
	void draw();
	void handleevents();
	void setHsize(float sizex,float sizey);
};
