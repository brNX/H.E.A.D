#include "Ball.h"
#include "LevelManager.h"
#include "Level.h"

Ball::Ball(void)
{
	type = O_INVALID;
	sprite = 0;
	bodyshape=0;
	body=0;
	radius=-1;
	pX=0;
	pY=0;
}

Ball::Ball(float radius,float x,float y)
{
	type = O_BALL;
	radius=radius;
	pX=x;
	pY=y;

	LevelManager * lm = LevelManager::getInstance();

	/**********codigo Box2D***************/
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(x,y);

	bodyshape=new b2CircleShape();
	((b2CircleShape*)bodyshape)->m_radius=radius;

	body=NULL;
	b2World * world = ((Level*)lm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);
	
	b2FixtureDef fd;
	fd.shape = bodyshape;
	fd.density = 1.0f;
	fd.friction = 0.3f;

	body->CreateFixture(&fd);
	/**************************************/


	/***********codigo CLanlib***************/
	sprite = lm->getSprite("ball");

}

Ball::~Ball(void)
{
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;

	if(sprite)
		delete sprite;
	sprite=0;
}

void Ball::draw(){

}

void Ball::handleevents(){

}

void Ball::setRadius(float r){
	radius=r;
}