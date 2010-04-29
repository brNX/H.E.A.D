#pragma once
#include "PhysicalObject.h"

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
	void roda(float angle);
private:
	float moveangle;
};
