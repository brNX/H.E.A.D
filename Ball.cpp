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

///construtor com posi��o e raio
Ball::Ball(float radius,float x,float y)
{
	type = O_BALL;
	this->radius=radius;
	ticks = 0;
	pX=x;
	pY=y;

	bump_sound = CL_SoundBuffer("clunk.wav");

	sm = ScreenManager::getInstance();

	/**********codigo Box2D***************/

	//define o tipo e a posição
	bodydef.type = b2_dynamicBody;
	bodydef.position.Set(x,y);
	bodydef.linearVelocity=b2Vec2(0.0f,-8.0f);

	//define a forma
	bodyshape=new b2CircleShape();
	((b2CircleShape*)bodyshape)->m_radius=radius;

	//cria o corpo usando as defini��es
	body=NULL;
	b2World * world = ((Level*)sm->getCurrentScreen())->getWorld();
	body = world->CreateBody(&bodydef);
	
	b2FixtureDef fd;
	fd.shape = bodyshape;
	fd.density = 1.0f;
	fd.friction = 0.3f;
	fd.restitution = 0.2f;

	body->CreateFixture(&fd);

	//usa o userdata para guardar um ponteiro no objecto body do Box2D (usado nas colis�es)
	body->SetUserData(this);

	/**************************************/


	/***********codigo CLanlib***************/
	//criar a sprite
	sprite = sm->getSprite("ball");
	sprite->set_linear_filter(true);

	//criar o collision outline (colis�es no clanlib , possivelmente sem uso)
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

//desenha o objecto
void Ball::draw(){

	sm->drawSprite(sprite,pX,pY);

	//outline de debug
	//sm->drawCoutline(&coutline,pX,pY);

}

void Ball::playsound(){
	if(ticks == 0){
		bump_sound.play();
		ticks = 60;
		printf("PLAY SOUND!!!");
	}
}

///vai buscar os dados da simula��o box2d e actualiza as corrdenadas
void Ball::handleevents(){

	pX=body->GetPosition().x;
	pY=body->GetPosition().y;
	angle = body->GetAngle();
	
	if(ticks > 0){
		ticks--;
	}
	float scale = sm->getScreenRatio() /(float)(sprite->get_height());
	
	sprite->set_angle(CL_Angle::from_radians(-angle));
	sprite->set_scale(scale*2,scale*2);
	
	coutline.set_scale(scale*2,scale*2);
	coutline.set_angle(CL_Angle::from_radians(-angle));

	float screenratio=sm->getScreenRatio();
	
	coutline.set_translation(pX*screenratio,sm->getScreensizey()-(pY*screenratio));
}
