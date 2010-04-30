#include "KinematicRamp.h"
#include "ScreenManager.h"
#include "Level.h"
#include <stdio.h>

KinematicRamp::KinematicRamp(void)
{
}

KinematicRamp::~KinematicRamp(void)
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

KinematicRamp::KinematicRamp(float x, float y)
{
	moveangle=0.0f;
	type = O_KRAMP;
	pX=x;
	pY=y;
	
	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/

	//define o tipo e a posição 
	bodydef.position.Set(x,y);
	bodydef.type = b2_kinematicBody;

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	b2Vec2 vect[4];
	
	vect[0]=b2Vec2(-3.836f,0.979f);	
	vect[1]=b2Vec2(-2.133f,	-0.91f);	
	vect[2]=b2Vec2(2.133f,	-0.91f);	
	vect[3]=b2Vec2(3.836f,0.979f);		

	b2PolygonShape shape;

	shape.Set(vect,4);

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.friction = 0.1f;
	fd.shape=&shape;

	//fd.restitution = 1.5f;

	body->CreateFixture(&fd);

	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colisões)
	body->SetUserData(this);


	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("krampa");
	sprite->set_linear_filter(true);

}

void KinematicRamp::draw()
{
	sm->drawSprite(sprite,pX,pY);
}

void KinematicRamp::handleevents()
{

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();
	body->SetTransform(body->GetPosition(),angle+moveangle);
	moveangle=0;
	float screenratio=sm->getScreenRatio();

	//dados do poligono
	
	//4.886 largura no ficheiro c4d
	//6 altura no ficheiro c4d
	
	float scalex = screenratio*7.672f /((float)sprite->get_width());
	float scaley = screenratio*1.889f /((float)sprite->get_height());

	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scalex,scaley);
}

void KinematicRamp::roda(float angle){
	moveangle-=CL_Angle::from_degrees(angle).to_radians();
}