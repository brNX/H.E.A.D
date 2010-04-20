#pragma once
#include "PhysicalObject.h"

class Ramp :
	public PhysicalObject
{
public:
	Ramp(void);
	Ramp(float x, float y);
	~Ramp(void);
public:	
	void draw();
	void handleevents();
};
