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
	inline float getRadius(){return radius;}
	inline void setRadius(float r){radius=r;}

};

