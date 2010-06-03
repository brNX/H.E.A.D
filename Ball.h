#pragma once
#include "PhysicalObject.h"
#include <ClanLib/sound.h>

class Ball :
	public PhysicalObject
{
public:
	Ball(void);
	Ball(float radius,float x, float y);
	~Ball(void);
private:
	float radius;
	int ticks;
	CL_SoundBuffer bump_sound;
public:	
	void draw();
	void handleevents();
	void playsound();
	inline float getRadius(){return radius;}
	inline void setRadius(float r){radius=r;}

};

