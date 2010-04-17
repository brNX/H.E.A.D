

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <Box2D/Box2D.h>

#include "app.h"
#include "Wiimote_handler.h"
#include "framerate_counter.h"

//1000 por ser millisegundos
#define DESIRED_FRAME_TIME 1000.0/60.0

int multiplicardorparabox2d=30;
b2Body* body;

// The start of the Application
int App::start(const std::vector<CL_String> &args)
{
		quit = false;
		Wiimote_handler wiimote;

		//wiimote.init();



		try
		{
			// Set the window
			// This opens a 640 x 480 window, including the frame size
			// If you want more control over the window, pass CL_DisplayWindowDescription to CL_DisplayWindow
			// (This is useful to create a borderless window of a specific size)
			// If you require target specific control over the window, use the derived CL_OpenGLWindowDescription
			// (This contains the multisampling options)

			//codigo para antialiasing/multisampling
			CL_OpenGLWindowDescription desc;
			desc.set_title("ClanLib Basic2D Example");
			desc.set_size( CL_Size(640, 480), false );
			desc.set_multisampling(4);
			CL_DisplayWindow window(desc);	

			//CL_DisplayWindow window("ClanLib Basic2D Example", 640, 480);

			// Connect the Window close event
			CL_Slot slot_quit = window.sig_window_close().connect(this, &App::on_window_close);

			// Connect a keyboard handler to on_key_up()
			CL_Slot slot_input_up = (window.get_ic().get_keyboard()).sig_key_up().connect(this, &App::on_input_up);

			// Get the graphic context
			CL_GraphicContext gc = window.get_gc();

			// Load a sprite from a png-file
			//CL_Sprite spr_logo(gc, "resources/logo.png");

			CL_ResourceManager resources("resources.xml");
			CL_Sprite ball(gc, "ball", &resources);
			ball.set_linear_filter(true);


			CL_Font fnt_clansoft;
			fnt_clansoft = CL_Font(gc, L"Tahoma", 32);


			// Define the gravity vector.
			b2Vec2 gravity(1.0f, -10.0f);

			// Do we want to let bodies sleep?
			bool doSleep = true;

			// Construct a world object, which will hold and simulate the rigid bodies.
			b2World world(gravity, doSleep);

			// Define the ground body.
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(0.0f, -9.0f);

			// Call the body factory which allocates memory for the ground body
			// from a pool and creates the ground box shape (also from a pool).
			// The body is also added to the world.
			b2Body* groundBody = world.CreateBody(&groundBodyDef);

			// Define the ground box shape.
			b2PolygonShape groundBox;

			// The extents are the half-widths of the box.
			groundBox.SetAsBox(20.0f, 10.0f);

			// Add the ground fixture to the ground body.
			groundBody->CreateFixture(&groundBox, 0.0f);

			//circulo


			// Define the dynamic body. We set its position and call the body factory.
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.position.Set(3.0f, 15.0f);
			body = world.CreateBody(&bodyDef);

			b2CircleShape dynamicCircle;
			dynamicCircle.m_radius=1;

			b2FixtureDef fd;
			fd.shape = &dynamicCircle;
			fd.density = 1.0f;
			fd.friction = 1.7f;
			body->CreateFixture(&fd);



			/*
			// Define another box shape for our dynamic body.
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(1.0f, 1.0f);

			// Define the dynamic body fixture.
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;

			// Set the box density to be non-zero, so it will be dynamic.
			fixtureDef.density = 1.0f;

			// Override the default friction.
			fixtureDef.friction = 0.3f;

			// Add the shape to the body.
			body->CreateFixture(&fixtureDef);

			*/

			// Prepare for simulation. Typically we use a time step of 1/60 of a
			// second (60Hz) and 10 iterations. This provides a high quality simulation
			// in most game scenarios.
			float32 timeStep = 1.0f / 60.0f;
			int32 velocityIterations = 6;
			int32 positionIterations = 2;

			FramerateCounter frameratecounter;

			//variaveis para o tamanho da janela
			//int tamanhoxmax=window.get_geometry().right-window.get_geometry().left;
			int tamanhoymax=window.get_geometry().bottom-window.get_geometry().top;

			//codigo clanlib para criar um rectangulo
			//CL_Rect rectangulo(CL_Size(multiplicardorparabox2d*2,multiplicardorparabox2d*2));
			CL_Rect ground(CL_Size(multiplicardorparabox2d*20*2,multiplicardorparabox2d*10*2));

			//centrar o rectangulo
			//rectangulo.translate(-rectangulo.get_center().x,-rectangulo.get_center().y);
			ground.translate(-ground.get_center().x,-ground.get_center().y);

			// Now print the position and angle of the body.
			b2Vec2 pos = groundBodyDef.position;
			int gposx = pos.x;
			int gposy = pos.y;


			// Run until someone presses escape
			int i = 0;
			while (!quit)
			{

				unsigned startTime = CL_System::get_time();

				// Instruct the world to perform a single step of simulation.
				// It is generally best to keep the time step and iterations fixed.
				world.Step(timeStep, velocityIterations, positionIterations);

				// Clear applied body forces. We didn't apply any forces, but you
				// should know about this function.
				world.ClearForces();

				// Now print the position and angle of the body.
				b2Vec2 position = body->GetPosition();
				float32 angle = body->GetAngle();

				//printf("angle : %f\n",angle);

				//brincadeira
				//rectangulo.set_size(CL_Size(multiplicardorparabox2d*2,multiplicardorparabox2d*2));
				ground.set_size(CL_Size(multiplicardorparabox2d*20*2,multiplicardorparabox2d*10*2));
				//centrar o rectangulo
				//rectangulo.translate(-rectangulo.get_center().x,-rectangulo.get_center().y);
				ground.translate(-ground.get_center().x,-ground.get_center().y);

				//CL_Rect rodado =  rectangulo.get_rot_bounds(rectangulo.get_center(),CL_Angle::from_radians(angle));

				// Clear the display in a dark blue nuance
				// The four arguments are red, green, blue and alpha
				gc.clear(CL_Colorf(0.0f,0.0f,0.2f));



				// ground e box a cair
				//CL_Draw::box(gc, (position.x*multiplicardorparabox2d + rodado.left), rodado.bottom+(tamanhoymax-(position.y*multiplicardorparabox2d)),rodado.right+(position.x*multiplicardorparabox2d),rodado.top+(tamanhoymax-(position.y*multiplicardorparabox2d)), CL_Colorf(1.0f, 0.0f, 0.0f));
				CL_Draw::box(gc, ground.left+(gposx*multiplicardorparabox2d),ground.bottom+(tamanhoymax-(gposy*multiplicardorparabox2d)),ground.right+(gposx*multiplicardorparabox2d),ground.top+(tamanhoymax-(gposy*multiplicardorparabox2d)),CL_Colorf(0.5f, 0.0f, 0.0f));

				// Draw a rectangle in the center of the screen
				// going from (240, 140) -> (440, 340) _not_ including the
				// pixels in the right-most column and bottom-most row (440, 340)
				//CL_Draw::fill(gc, CL_Rectf((position.x*multiplicardorparabox2d + rodado.left), rodado.top+(tamanhoymax-(position.y*multiplicardorparabox2d)), rodado.right+(position.x*multiplicardorparabox2d), rodado.bottom+(tamanhoymax-(position.y*multiplicardorparabox2d))), CL_Colorf(1.0f, 0.5f, 1.0f));

				//CL_Draw::gradient_circle(gc,CL_Pointf(position.x*multiplicardorparabox2d,tamanhoymax-(position.y*multiplicardorparabox2d)),1.0*multiplicardorparabox2d,CL_Gradient(CL_Colorf(0.1f, 0.1f, 0.4f),CL_Colorf(0.8f,0.8f,0.8f)));

				float scale = multiplicardorparabox2d/(float)(ball.get_height());
				ball.set_angle(CL_Angle::from_radians(-angle));
				ball.set_scale(scale*2,scale*2);
				ball.draw(gc,position.x*multiplicardorparabox2d,tamanhoymax-(position.y*multiplicardorparabox2d));

				// Show the logo image.
				// Use the get_width() and get_height() functions of both
				// CL_DisplayWindow and CL_Sprite, to show the image in the bottom right corner
				/*spr_logo.draw(gc,
					(float) gc.get_width()-spr_logo.get_width(),
					(float) gc.get_height()-spr_logo.get_height());
				*/

				CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
				fnt_clansoft.draw_text(gc, 20, 30, fps);


				// Flip the display, showing on the screen what we have drawed
				// since last call to flip()
				window.flip(1);

				// This call processes user input and other events
				CL_KeepAlive::process(0);

				//usleep(20000);

				//poll da wiimote
				//wiimote.poll();

				unsigned drawTime = CL_System::get_time() - startTime;
				if(DESIRED_FRAME_TIME > drawTime)
					CL_System::sleep( DESIRED_FRAME_TIME - drawTime );
				frameratecounter.frame_shown();
				i++;

				//if (i==60) quit= true;
			}
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();
		//wiimote.release();

		return -1;
	}
	//wiimote.release();
	return 0;
}

// A key was pressed
void App::on_input_up(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_ESCAPE)
	{
		quit = true;
	}

	if(key.id == CL_KEY_A)
		multiplicardorparabox2d++;

	if (key.id == CL_KEY_Z)
		multiplicardorparabox2d--;

	if(key.id == CL_KEY_UP){
	b2Vec2 direction(0,20);
	body->SetActive(true);
	body->ApplyLinearImpulse(direction,body->GetPosition());

	}

	if(key.id == CL_KEY_DOWN){
	b2Vec2 direction(0,-20);
	body->SetActive(true);
	body->ApplyLinearImpulse(direction,body->GetPosition());
	}



	if(key.id == CL_KEY_LEFT){
	b2Vec2 direction(-20,0);
	body->SetActive(true);
	body->ApplyLinearImpulse(direction,body->GetPosition());

	}

	if(key.id == CL_KEY_RIGHT){
	b2Vec2 direction(20,0);
	body->SetActive(true);
	body->ApplyLinearImpulse(direction,body->GetPosition());
	}
}

// The window was closed
void App::on_window_close()
{
	quit = true;
}
