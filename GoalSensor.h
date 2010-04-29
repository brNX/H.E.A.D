#pragma once
#include "PhysicalObject.h"

class GoalSensor :
	public PhysicalObject
{
public:
	GoalSensor(void);
	GoalSensor(float x, float y);
	~GoalSensor(void);
public:
	void draw();
	void handleevents();
};
