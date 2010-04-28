#pragma once
#include "physicalobject.h"

class Trampolim :
	public PhysicalObject
{
public:
	Trampolim(void);
	Trampolim(float x,float y);
	~Trampolim(void);
public:	
	void draw();
	void handleevents();
};
