#include "Ramp.h"
#include "Level.h"
#include "ScreenManager.h"

Ramp::Ramp(void)
{
}

Ramp::~Ramp(void)
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

Ramp::Ramp(float x, float y)
{
	type = O_RAMP;
	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/

	//define o tipo e a posição 
	bodydef.position.Set(x,y);

	//define a forma

	// This defines a triangle in CCW order.

	b2Vec2 vertices[3];
	b2Vec2 vrect[5];

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);
	
	vrect[0].Set(0.0f, 0.0f);
	vrect[1].Set(3.0f, 0.0f);
	vrect[2].Set(3.0f, 0.6f);
	vrect[3].Set(0.0f, 0.6f);
	
	b2PolygonShape shape;
	
	shape.Set(vrect,4);

	body->CreateFixture(&shape,0.0f);
		
	vrect[3].Set(0.0f, 0.6f);
	vrect[2].Set(0.0f, 3.0f);
	vrect[1].Set(0.6f, 3.0f);
	vrect[0].Set(0.6f, 0.6f);

	shape.Set(vrect,4);

	body->CreateFixture(&shape,0.0f);
	
	
	vertices[2].Set(0.61f, 0.6f);
	vertices[1].Set(0.6f, 3.0f);
	vertices[0].Set(0.695f, 2.311f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	
	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(0.695f, 2.311f);
	vertices[0].Set(0.878f, 1.869f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(0.878f, 1.869f);
	vertices[0].Set(1.0f, 1.664f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);
	
	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(1.0f, 1.664f);
	vertices[0].Set(1.297f, 1.307f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(1.297f, 1.307f);
	vertices[0].Set(1.477f, 1.142f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(1.477f, 1.142f);
	vertices[0].Set(1.87f, 0.882f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	vertices[2].Set(0.6f, 0.6f);
	vertices[1].Set(1.87f, 0.882f);
	vertices[0].Set(2.3f, 0.705f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);

	vertices[2].Set(0.6f, 0.6f);
	vertices[0].Set(3.0f, 0.6f);
	vertices[1].Set(2.3f, 0.705f);

	shape.Set(vertices,3);

	body->CreateFixture(&shape,0.0f);


	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colisões)
	body->SetUserData(this);

	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("rampa");
	sprite->set_linear_filter(true);

}


void Ramp::draw()
{
	sm->drawSprite(sprite,pX,pY);
}

void Ramp::handleevents()
{

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	float screenratio=sm->getScreenRatio();

	//dados do poligono
	float scalex = screenratio*3.0f /((float)sprite->get_width());
	float scaley = screenratio*3.0f /((float)sprite->get_height());

	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scalex,scaley);
}