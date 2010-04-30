#pragma once
#include "PhysicalObject.h"

class StartRamp :
	public PhysicalObject
{
public:
	StartRamp(void);
	StartRamp(float x, float y);
	~StartRamp(void);
public:	
	void draw();
	void handleevents();
};
