#include "Trampolim.h"
#include "ScreenManager.h"
#include "Level.h"
#include "triangulate.h"
#include <stdio.h>

Trampolim::Trampolim(void)
{
}

Trampolim::~Trampolim(void)
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

Trampolim::Trampolim(float x, float y)
{
	type = O_TRAMPOLIN;
	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/

	//define o tipo e a posi��o 
	bodydef.position.Set(x,y);
	bodydef.type = b2_kinematicBody;
	bodydef.linearVelocity=b2Vec2(0.0f,0.4f);

	//cria o corpo usando as defini��es
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.friction = 0.3f;
	fd.restitution = 3.0f;

	//uso do triangulate.cpp -> pega num poligono e divide em triangulos
	Vector2dVector a;

	a.insert(a.begin(),b2Vec2(5.0f,	0.0f));	
	a.insert( a.begin(),b2Vec2(0.0f,	0.0f));	
	a.insert( a.begin(),b2Vec2(0.0f,	2.0f));	
	a.insert( a.begin(),b2Vec2(1.396f,	1.636f));	
	a.insert( a.begin(),b2Vec2(3.324f,	1.36f));	
	a.insert( a.begin(),b2Vec2(5.0f,	1.251f	));
	a.insert( a.begin(),b2Vec2(6.676f,	1.36f	));
	a.insert( a.begin(),b2Vec2(8.604f,	1.636f));	
	a.insert(a.begin(), b2Vec2(10.0f,	2.0f));	
	a.insert(a.begin(), b2Vec2(10.0f,	0.0f));	
	
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

		fd.shape = (b2Shape*)&shape;

		body->CreateFixture(&fd);

		printf("Triangle %d => (%f,%f) (%f,%f) (%f,%f)\n",i+1,vect[0].x,vect[0].y,vect[1].x,vect[1].y,vect[2].x,vect[2].y);
	}


	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colis�es)
	body->SetUserData(this);

	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("trampolim");
	sprite->set_linear_filter(true);

}


void Trampolim::draw()
{
	sm->drawSprite(sprite,pX,pY);
}

void Trampolim::handleevents()
{

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	float screenratio=sm->getScreenRatio();

	//dados do poligono
	
	//4.886 largura no ficheiro c4d
	//6 altura no ficheiro c4d
	
	float scalex = screenratio*10.0f /((float)sprite->get_width());
	float scaley = screenratio*2.0f /((float)sprite->get_height());

	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scalex,scaley);
}
