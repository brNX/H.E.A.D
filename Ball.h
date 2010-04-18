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
public:	
	void draw();
	void handleevents();
	void setRadius(float r);
	inline float getRadius(){return radius;}
};

