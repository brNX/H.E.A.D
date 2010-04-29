/*
 * Goal.cpp
 *
 *  Created on: Apr 29, 2010
 *      Author: bgouveia
 */

#include "Goal.h"

Goal::Goal() {
	sm = ScreenManager::getInstance();
	type = O_INVALID;
	bodyshape=0;
	body=0;
	hsizeX=-1;
	hsizeY=-1;
	pX=0;
	pY=0;
}

Goal::Goal(float x,float y){
	type = O_GOAL;

	pX=x;
	pY=y;

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/
	//define a posi��o
	bodydef.position.Set(x,y);

	//cria a forma
	bodyshape=new b2PolygonShape();
	((b2PolygonShape*)bodyshape)->SetAsBox(hsizeX,hsizeY);

	//cria o corpo usando as defini��es
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	body->CreateFixture(bodyshape,0.0f);

	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colis�es)
	body->SetUserData(this);
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

	//TODO: usar sprite(s) e codigo do goal

	CL_Rectf ground(CL_Sizef(hsizeX*2,hsizeY*2));

	//centrar o rectangulo
	ground.translate(-ground.get_center().x,-ground.get_center().y);
	CL_Colorf color(0.5f,0.5f,0.5f);
	sm->drawBox(ground.left+pX,ground.bottom+pY,ground.right+pX,ground.top+pY,color);

	//sm->drawCoutline(&coutline,pX,pY);

}

///vai buscar os dados da simula��o box2d e actualiza as corrdenadas
void Goal::handleevents(){

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();

	//por enquanto so para teste (colis�es clanlib)
	float screenratio=sm->getScreenRatio();

	float scalex = screenratio*hsizeX /((float)coutline.get_width());
	float scaley = screenratio*hsizeY /((float)coutline.get_height());
	coutline.set_scale(scalex*2,scaley*2);

	coutline.set_translation(pX*screenratio,((float)sm->getScreensizey())-(pY*screenratio));

}
