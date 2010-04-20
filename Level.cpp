#include "Level.h"
#include "PhysicalObject.h"
#include "Ball.h"
#include "Block.h"


// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
#define timeStep 1.0f / 60.0f
#define velocityIterations  6
#define positionIterations  2


Level::Level(void)
{

	// Define the gravity vector.
	b2Vec2 gravity(1.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world= new b2World(gravity, doSleep);

	world->SetContactListener((b2ContactListener*)&listener);

}

Level::~Level(void)
{
	if (gameBall)
		delete gameBall;
	gameBall=0;

	if (levelitems.size()>0)
		levelitems.clear();

	if(world)
		delete world;
	world=0;
}

void Level::HandleEvents(){
	//todo: logica do nivel e input output

	// Instruct the world to perform a single step of simulation.
	// It is generally best to keep the time step and iterations fixed.
	world->Step(timeStep, velocityIterations, positionIterations);

	// Clear applied body forces. We didn't apply any forces, but you
	// should know about this function.
	world->ClearForces();

	gameBall->handleevents();

	for (unsigned int i=0;i<levelitems.size();i++){
		levelitems[i]->handleevents();
		/*if(gameBall->getCollisionOutline()->collide(*(levelitems[i]->getCollisionOutline()))){
			printf("sim\n");	
		}else
			printf("nao\n");*/
	}


}

void Level::draw(){
	gameBall->draw();

	for (unsigned int i=0;i<levelitems.size();i++){
		levelitems[i]->draw();
	}
}

void Level::setupLevel(){

	//todo:carregar objectos de algum ficheiro ou assim

	gameBall = new Ball(1.0f,3.0f,15.0f);
	levelitems.push_back(new Block(20.0f,10.0f,0.0f,-9.0f));
	levelitems.push_back(new Block(2.0f,1.0f,20.0f,2.0f));

}