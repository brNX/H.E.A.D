#include "Ramp.h"
#include "Level.h"
#include "ScreenManager.h"
#include "triangulate.h"

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

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	//uso do triangulate.cpp -> pega num poligono e divide em triangulos
	Vector2dVector a;
	
	a.push_back( b2Vec2( 0.6f,3.0f));	
	a.push_back( b2Vec2(0.0f,3.0f));
	a.push_back( b2Vec2(0.0f,0.0f));
	a.push_back( b2Vec2(3.0f,0.0f));	
	a.push_back( b2Vec2(3.0f,0.6f));
	a.push_back( b2Vec2(2.768f,0.612f));	
	a.push_back( b2Vec2(2.535f,0.645f));	
	a.push_back( b2Vec2(2.3f,0.705f));
	a.push_back( b2Vec2(2.078f,0.785f));	
	a.push_back( b2Vec2(1.87f,0.882f));	
	a.push_back( b2Vec2(1.672f,0.998f));
	a.push_back( b2Vec2(1.477f,1.142f));	
	a.push_back( b2Vec2(1.297f,1.307f));
	a.push_back( b2Vec2(1.143f,1.475f));
	a.push_back( b2Vec2(1.0f,1.664f	));
	a.push_back( b2Vec2(0.878f,1.869f));
	a.push_back( b2Vec2(0.776f,2.087f));	
	a.push_back( b2Vec2(0.695f,2.311f));	
	a.push_back( b2Vec2(0.635f,2.547f));	
	a.push_back( b2Vec2(0.6f,2.8f));

	Vector2dVector result;

	//  Invoke the triangulator to triangulate this polygon.
	Triangulate::Process(a,result);

	// print out the results.
	int tcount = result.size()/3;

	for (int i=0; i<tcount; i++)
	{
		b2Vec2 vect[3];

		vect[0] = result[i*3+0];
		vect[1] = result[i*3+1];
		vect[2] = result[i*3+2];

		b2PolygonShape shape;

		shape.Set(vect,3);

		body->CreateFixture(&shape,0.0f);

		printf("Triangle %d => (%f,%f) (%f,%f) (%f,%f)\n",i+1,vect[0].x,vect[0].y,vect[1].x,vect[1].y,vect[2].x,vect[2].y);
	}

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