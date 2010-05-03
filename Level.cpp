#include "Level.h"
#include "PhysicalObject.h"
#include "Ball.h"
#include "Block.h"
#include "StartRamp.h"
#include "Trampolim.h"
#include "Goal.h"
#include "GoalSensor.h"
#include "Pit.h"
#include "KinematicRamp.h"
#include "ScreenManager.h"



///constantes da simulacao do Box2D
// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
#define timeStep 1.0f / 60.0f
#define velocityIterations  6
#define positionIterations  2


Level::Level(CL_String _name,int _levelindex)
{
	name = _name;
	levelindex=_levelindex;
	world=0;
	gameBall=0;
	restart();
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

	// percorre os objectos todos do nivel e chama handleevents
	gameBall->handleevents();

	for (unsigned int i=0;i<levelitems.size();i++){
		levelitems[i]->handleevents();
	}

}

///draw :-p
void Level::draw(){
	gameBall->draw();

	for (unsigned int i=0;i<levelitems.size();i++){
		levelitems[i]->draw();
	}
}

///incializa os objectos do nivel
void Level::setupLevel(){




	//todo:carregar objectos de algum ficheiro ou assim
	if(levelindex==1)
		gameBall = new Ball(1.0f,3.0f,15.0f);
	else
		gameBall = new Ball(1.0f,3.0f,20.0f);
	
	levelitems.push_back(new StartRamp(1.45f,1.0f));
	
	if(levelindex==1){
	levelitems.push_back(new Block(17.0f/2.0f,9.237f/2.0f,8.735f,-3.691f));
	levelitems.push_back(new Block(5.326f/2.0f,9.237f/2.0f,27.089f,-3.691f));
	levelitems.push_back(new Pit(6.991f/2.0f,5.925f/2.0f,20.875f,-4.476f));
	levelitems.push_back(new Pit(28.714f/2.0f,5.925f/2.0f,-14.252f,-4.476f));
	levelitems.push_back(new Trampolim(13.0f,1.0f));
	currentControllableObject = levelitems.at(levelitems.size()-1);
	levelitems.push_back(new Goal(27.0f,1.0f));
	levelitems.push_back(new GoalSensor(27.0f,1.0f));
	}else{
	levelitems.push_back(new Block(8.396f/2.0f,9.237f/2.0f,4.516f,-3.691f));
	levelitems.push_back(new Pit(8.396f/2.0f,9.237f/2.0f,12.972f,-3.691f));
	levelitems.push_back(new Pit(28.714f/2.0f,5.925f/2.0f,-14.252f,-4.476f));
	levelitems.push_back(new Block(5.326f/2.0f,9.237f/2.0f,22.587f,-3.691f));
	levelitems.push_back(new Block(2.579f/2.0f,19.34f/2.0f,18.597f,-3.691f));
	levelitems.push_back(new Block(2.338f/2.0f,27.34f/2.0f,26.512f,-3.064f));
	levelitems.push_back(new Goal(22.587f,1.0f));
	levelitems.push_back(new GoalSensor(22.587f,1.0f));
	levelitems.push_back(new KinematicRamp(10.849f,4.129f));
	currentControllableObject = levelitems.at(levelitems.size()-1);
	}
}

/// A key was pressed
void Level::on_input_down(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_ESCAPE)
	{
		printf("escape\n");
	}
	
	if (key.id == CL_KEY_R)
	{
		ScreenManager::getInstance()->setScreenType(S_PLAYING);
		restart();
		setupLevel();
	}
	
	if(key.id == CL_KEY_2){
		printf("2\n");
		ScreenManager::getInstance()->setScreenType(S_PLAYING);
		levelindex=2;
		restart();
		setupLevel();
	}
	
	if(key.id == CL_KEY_1){
		printf("1\n");
		ScreenManager::getInstance()->setScreenType(S_PLAYING);
		levelindex=1;
		restart();
		setupLevel();
	}

	if(key.id == CL_KEY_UP){
		printf("down\n");
	}

	if(key.id == CL_KEY_DOWN){
		printf("down\n");
	}

	
	if(key.id == CL_KEY_LEFT){
		printf("left\n");
		/*if(currentControllableObject->getType()==O_TRAMPOLIN)
			((Trampolim*)currentControllableObject)->roda(-1);
		if(currentControllableObject->getType()==O_KRAMP)
			((KinematicRamp*)currentControllableObject)->roda(-1);*/
	}

	if(key.id == CL_KEY_RIGHT){
		printf("right\n");
		/*if(currentControllableObject->getType()==O_TRAMPOLIN)
			((Trampolim*)currentControllableObject)->roda(1);
		if(currentControllableObject->getType()==O_KRAMP)
			((KinematicRamp*)currentControllableObject)->roda(1);*/
	}
	
}

void Level::restart(){

	if (gameBall)
		delete gameBall;
	gameBall=0;

	if (levelitems.size()>0)
		levelitems.clear();

	if (world)
		delete world;
	world=0;

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Do we want to let bodies sleep?
	bool doSleep = true;

	// Construct a world object, which will hold and simulate the rigid bodies.
	world= new b2World(gravity, doSleep);

	//inicializa o listener para contactos entre objectos no mundo
	world->SetContactListener((b2ContactListener*)&listener);
}


void Level::wiimote_input(float pitch,bool one , bool two){
	if(currentControllableObject->getType()==O_TRAMPOLIN)
		((Trampolim*)currentControllableObject)->setRotation(CL_Angle::from_degrees(pitch).to_radians());
	if(currentControllableObject->getType()==O_KRAMP)
		((KinematicRamp*)currentControllableObject)->setRotation(CL_Angle::from_degrees(pitch).to_radians());

	if(two){
		printf("2\n");
		ScreenManager::getInstance()->setScreenType(S_PLAYING);
		levelindex=2;
		restart();
		setupLevel();
	}
	
	if(one){
		printf("1\n");
		ScreenManager::getInstance()->setScreenType(S_PLAYING);
		levelindex=1;
		restart();
		setupLevel();
	}
}