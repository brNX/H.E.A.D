#pragma once
#include "physicalobject.h"

class KinematicRamp :
	public PhysicalObject

{
public:
	KinematicRamp(void);
	~KinematicRamp(void);
	KinematicRamp(float x,float y);
public:	
	void draw();
	void handleevents();
	void roda(float angle);
private:
	float moveangle;
};
