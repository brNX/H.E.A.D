/*
 * Goal.cpp
 *
 *  Created on: Apr 29, 2010
 *      Author: bgouveia
 */

#include "Goal.h"
#include "ScreenManager.h"
#include "Level.h"
#include "triangulate.h"
#include <stdio.h>

Goal::Goal() {
	sm = ScreenManager::getInstance();
	type = O_INVALID;
	bodyshape=0;
	body=0;
	pX=0;
	pY=0;
}

Goal::Goal(float x,float y){
	type = O_GOAL;

	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/
	//define a posição
	bodydef.position.Set(x,y);

	//cria o corpo usando as definições
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	b2FixtureDef fd;
	fd.density = 1.0f;
	fd.friction = 0.3f;

	//uso do triangulate.cpp -> pega num poligono e divide em triangulos
	Vector2dVector a;

	a.push_back(b2Vec2(	-2.0f,	4.0f));	
	a.push_back(b2Vec2(-1.081f,	0.0f));		
	a.push_back(b2Vec2(0.0f,	0.0f));	
	a.push_back(b2Vec2(1.081f,	0.0f));		
	a.push_back(b2Vec2(2.0f,	4.0f));	
	a.push_back(b2Vec2(1.747f,	4.0f));		
	a.push_back(b2Vec2(0.858f,	0.217f));		
	a.push_back(b2Vec2(0.0f,	0.208f));		
	a.push_back(b2Vec2(-0.858f,	0.217f));		
	a.push_back(b2Vec2(-1.747f,	4.0f));		
	
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
	sprite = sm->getSprite("goal");
	sprite->set_linear_filter(true);
}

Goal::~Goal() {
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;
}

///desenha o bloco
void Goal::draw(){
	sm->drawSprite(sprite,pX,pY);
}

///vai buscar os dados da simulação box2d e actualiza as corrdenadas
void Goal::handleevents(){

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	//por enquanto so para teste (colisões clanlib)
	float screenratio=sm->getScreenRatio();

	float scalex = screenratio*4.0f /((float)sprite->get_width());
	float scaley = screenratio*4.0f /((float)sprite->get_height());

	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scalex,scaley);

}
