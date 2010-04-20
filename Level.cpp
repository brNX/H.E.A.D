#include "Level.h"
#include "PhysicalObject.h"
#include "Ball.h"
#include "Block.h"


Level::Level(void)
{

	// Define the gravity vector.
	b2Vec2 gravity(1.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world= new b2World(gravity, doSleep);

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

}