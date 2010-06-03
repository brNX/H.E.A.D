#pragma once
#include "physicalobject.h"

class Bumper :
	public PhysicalObject
{
public:
	Bumper(void);
	Bumper(float x, float y);
	~Bumper(void);
public:
	void draw();
	void handleevents();


};
