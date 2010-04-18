#pragma once
#include "PhysicalObject.h"

class Ball :
	public PhysicalObject
{
public:
	Ball(void);
	Ball(float radius,float x, float y);
	~Ball(void);
private:
	float radius;
	float pX,pY;
public:	
	void draw();
	void handleevents();
	void setRadius(float r);
	void setPosition(float x , float y);
	float getRadius();
};

