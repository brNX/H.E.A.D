#pragma once

#include <ClanLib/display.h>
#include <Box2D/Box2D.h>

//forward declaration do screenmanager
class ScreenManager;

enum EObjectType
{
	O_BLOCK,
	O_BALL,
	O_TRAMPOLIN,
	O_PIT,
	O_GOAL,
	O_GOALSENSOR,
	O_STARTRAMP,
	O_KRAMP,
	O_BUMPER,
	O_INVALID
};

class PhysicalObject
{
public:
	PhysicalObject(void);
	virtual ~PhysicalObject(void);
protected:
	EObjectType type;
	
	CL_Sprite * sprite;
	CL_CollisionOutline coutline;
	
	b2Body * body;
	b2BodyDef bodydef;
	b2Shape * bodyshape;
	b2FixtureDef fixturedef;
	
	float pX,pY;
	float angle;

	ScreenManager * sm;

public:
	virtual void draw();
	virtual void handleevents();
	EObjectType getType();
	void setPosition(float x , float y);
	inline CL_CollisionOutline * getCollisionOutline(){return &coutline;}
};
