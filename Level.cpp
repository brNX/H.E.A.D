#include "Level.h"
#include "PhysicalObject.h"
#include "Ball.h"
#include "Bumper.h"
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
	//dicionario para string->enum
	dict[CL_String("Ball")]=O_BALL;
	dict[CL_String("Block")]=O_BLOCK;
	dict[CL_String("StartRamp")]=O_STARTRAMP;
	dict[CL_String("Pit")]=O_PIT;
	dict[CL_String("Trampolin")]=O_TRAMPOLIN;
	dict[CL_String("Goal")]=O_GOAL;
	dict[CL_String("GoalSensor")]=O_GOALSENSOR;
	dict[CL_String("KinematicRamp")]=O_KRAMP;
	dict[CL_String("Bumper")]=O_BUMPER;

	name = _name;
	printf("name : %s\n",name.c_str());
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
	bool controllable;

	//vai buscar o nome dos niveis ao ficheiro xml
	CL_File file(name, CL_File::open_existing, CL_File::access_read);
	CL_DomDocument document;
	document.load(file);

	CL_DomNode root = document.get_first_child();
	CL_DomNode current = root.get_first_child();

	printf("conteudo niveis?\n");
	while (!current.is_null()){
		controllable = false;

		CL_String type = current.to_element().get_attribute("type");
		if (current.to_element().has_attribute("controllable")){
			if(current.to_element().get_attribute("controllable").compare("true") == 0){
				controllable = true;
			}
		}

		printf("objecto: %s\n",type.c_str());
		printf("enum: %d\n",dict[type]);
		float radius;
		float hsizex;
		float hsizey;
		float forceX, forceY;
		
		//posicao
		CL_DomNode child = current.get_first_child();
		float x = CL_StringHelp::text_to_float(child.to_element().get_attribute("x").c_str());
		float y = CL_StringHelp::text_to_float(child.to_element().get_attribute("y").c_str());
		printf("pos: %f %f\n",x,y);

		switch(dict[type]){

		case O_BLOCK:
			child=child.get_next_sibling();
			hsizex = CL_StringHelp::text_to_float(child.to_element().get_attribute("x").c_str());
			hsizey = CL_StringHelp::text_to_float(child.to_element().get_attribute("y").c_str());
			levelitems.push_back(new Block(hsizex,hsizey,x,y));
			break;

		case O_PIT:
			child=child.get_next_sibling();
			hsizex = CL_StringHelp::text_to_float(child.to_element().get_attribute("x").c_str());
			hsizey = CL_StringHelp::text_to_float(child.to_element().get_attribute("y").c_str());
			levelitems.push_back(new Pit(hsizex,hsizey,x,y));
			break;
		
		case O_BALL: 
			child=child.get_next_sibling();
			radius= CL_StringHelp::text_to_float(child.to_element().get_text());
			printf("radius: %f\n",radius);
			child=child.get_next_sibling();
			forceX = CL_StringHelp::text_to_float(child.to_element().get_attribute("x").c_str());
			forceY = CL_StringHelp::text_to_float(child.to_element().get_attribute("y").c_str());
			gameBall = new Ball(radius,x,y, forceX, forceY);
			break;
		
		case O_STARTRAMP:
			levelitems.push_back(new StartRamp(x,y));
			break;
		
		case O_KRAMP: 
			levelitems.push_back(new KinematicRamp(x,y));
			if(controllable){
				controllableObjects.push_back(levelitems.at(levelitems.size()-1));
			}else{
				if(child.to_element().has_attribute("angle")){
					float angle = CL_StringHelp::text_to_float(child.to_element().get_attribute("angle").c_str());
					((KinematicRamp*)levelitems.at(levelitems.size()-1))->setRotation(CL_Angle::from_degrees(angle).to_radians());
				}
			}
			
			break;

		case O_BUMPER: 
			levelitems.push_back(new Bumper(x,y));
			break;
		
		case O_TRAMPOLIN: 
			levelitems.push_back(new Trampolim(x,y));
			//por enquanto...
			if(controllable){
				controllableObjects.push_back(levelitems.at(levelitems.size()-1));
			}else{
				if(child.to_element().has_attribute("angle")){
					float angle = CL_StringHelp::text_to_float(child.to_element().get_attribute("angle").c_str());
					((Trampolim*)levelitems.at(levelitems.size()-1))->setRotation(CL_Angle::from_degrees(angle).to_radians());
				}
			}
			break;

		case O_GOAL: 
			levelitems.push_back(new Goal(x,y)); 
			break;

		case O_GOALSENSOR:
			levelitems.push_back(new GoalSensor(x,y));
			break;
		}

		//levelnames.push_back(level);
		current=current.get_next_sibling();
	}

	//todo:carregar objectos de algum ficheiro ou assim
	/*if(levelindex==1)
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
	}*/
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


void Level::wiimote_input(float pitch){
	PhysicalObject * currentControllableObject;

	for(int i=0; i<controllableObjects.size(); i++){
		currentControllableObject = controllableObjects.at(i);

		if(currentControllableObject->getType()==O_TRAMPOLIN)
			((Trampolim*)currentControllableObject)->setRotation(CL_Angle::from_degrees(pitch).to_radians());
		if(currentControllableObject->getType()==O_KRAMP)
			((KinematicRamp*)currentControllableObject)->setRotation(CL_Angle::from_degrees(pitch).to_radians());
	}
	
}