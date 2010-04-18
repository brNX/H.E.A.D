#include "Ball.h"

Ball::Ball(void)
{
	type = O_INVALID;
	bodyshape=NULL;
	body=NULL;
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

	/**********codigo Box2D***************/
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(x,y);

	bodyshape=new b2CircleShape();
	((b2CircleShape*)bodyshape)->m_radius=radius;

	//TODO: usar o levelmanager/ou screenmanager para inserir objecto no world do box2d
	body=NULL;
	//body = world.CreateBody(&bodyDef);
	
	b2FixtureDef fd;
	fd.shape = bodyshape;
	fd.density = 1.0f;
	fd.friction = 0.3f;

	//TODO:body->CreateFixture(&fd);
	/**************************************/


	/***********codigo CLanlib***************/
	//TODO: usar o levelmanager /ou screenmanager para criar o sprite e o CL_collisionoutline

}

Ball::~Ball(void)
{
	if(bodyshape)
		delete bodyshape;
	bodyshape=NULL;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=NULL;
}

void Ball::draw(){

}

void Ball::handleevents(){

}

void Ball::setRadius(float r){
	radius=r;
}

float Ball::getRadius(){
	return radius;
}

void Ball::setPosition(float x , float y){
	pX=x;
	pY=y;
}

