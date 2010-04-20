#include "Block.h"
#include "LevelManager.h"
#include "Level.h"

Block::Block(void)
{
	type = O_INVALID;
	bodyshape=0;
	body=0;
	hsizeX=-1;
	hsizeY=-1;
	pX=0;
	pY=0;
}

Block::Block(float hsizex,float hsizey,float x, float y){
	
	type = O_BLOCK;

	pX=x;
	pY=y;
	hsizeX=hsizex;
	hsizeY=hsizey;
				
	LevelManager * lm = LevelManager::getInstance();

	/**********codigo Box2D***************/
	bodydef.position.Set(x,y);

	bodyshape=new b2PolygonShape();
	((b2PolygonShape*)bodyshape)->SetAsBox(hsizeX,hsizeY);

	body=NULL;
	b2World * world = ((Level*)lm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);

	body->CreateFixture(bodyshape,0.0f);


	/**************************************/


	/***********codigo CLanlib***************/
	//todo: usar sprite depois
	//sprite = lm->getSprite("ball");
	//sprite->set_linear_filter(true);
}

Block::~Block(void)
{
	if(bodyshape)
		delete bodyshape;
	bodyshape=0;

	if(body)
		body->GetWorld()->DestroyBody(body);
	body=0;
}

void Block::draw(){

	CL_Rectf ground(CL_Sizef(hsizeX*2,hsizeY*2));

	//centrar o rectangulo
	ground.translate(-ground.get_center().x,-ground.get_center().y);


	LevelManager * lm = LevelManager::getInstance();

	// Now print the position and angle of the body.
	b2Vec2 position = body->GetPosition();
	float angle = body->GetAngle();

	//TODO: testar isto
	lm->drawBox(ground.left+pX,ground.bottom+pY,ground.right+pX,ground.top+pY,CL_Colorf(0.5f,0.5f,0.5f));

}

void Block::handleevents(){

}