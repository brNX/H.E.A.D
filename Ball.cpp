#include "Ball.h"
#include "ScreenManager.h"
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
	sm = ScreenManager::getInstance();
}

Ball::Ball(float radius,float x,float y)
{
	type = O_BALL;
	this->radius=radius;
	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(x,y);

	bodyshape=new b2CircleShape();
	((b2CircleShape*)bodyshape)->m_radius=radius;

	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);
	
	b2FixtureDef fd;
	fd.shape = bodyshape;
	fd.density = 1.0f;
	fd.friction = 0.3f;

	body->CreateFixture(&fd);
	body->SetUserData(this);

	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("ball");
	sprite->set_linear_filter(true);

	//criar o collision outline
	coutline = CL_CollisionOutline("resources/ballc.png");
	coutline.set_alignment(origin_center);
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

	sm->drawSprite(sprite,pX,pY);
	sm->drawCoutline(&coutline,pX,pY);

}

void Ball::handleevents(){

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	float scale = sm->getScreenRatio() /(float)(sprite->get_height());
	
	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scale*2,scale*2);
	
	coutline.set_scale(scale*2,scale*2);
	coutline.set_angle(CL_Angle::from_radians(-angle));

	float screenratio=sm->getScreenRatio();
	
	coutline.set_translation(pX*screenratio,sm->getScreensizey()-(pY*screenratio));
}

void Ball::setRadius(float r){
	radius=r;
}
