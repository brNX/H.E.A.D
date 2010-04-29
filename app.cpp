

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <Box2D/Box2D.h>

#include "app.h"
#include "Wiimote_handler.h"
#include "framerate_counter.h"

///1000 por ser millisegundos
#define DESIRED_FRAME_TIME 1000.0/60.0

///ratio screen/Box2D
#define DEFAULTSCREENRATIO 30


/// The start of the Application
int App::start(const std::vector<CL_String> &args)
{
		quit = false;
		
		try
		{

			//codigo para antialiasing/multisampling
			CL_OpenGLWindowDescription desc;
			desc.set_title("H.E.A.D");
			desc.set_size( CL_Size(1024, 768), false );
			desc.set_multisampling(8);
			CL_DisplayWindow window(desc);	

			// Connect the Window close event
			CL_Slot slot_quit = window.sig_window_close().connect(this, &App::on_window_close);

			// Get the graphic context
			CL_GraphicContext gc = window.get_gc();

			//get instance do screenmanager(singleton)
			sm = ScreenManager::getInstance();

			// Connect a keyboard handler to on_key_up()
			CL_Slot slot_input_up = (window.get_ic().get_keyboard()).sig_key_down().connect(sm,&ScreenManager::on_input_down);
			
			//passa a janela
			sm->setWindow(&window);

			sm->setScreenRatio(DEFAULTSCREENRATIO);

			//inicia os objectos
			sm->start();

			//framcounter so naquela...
			FramerateCounter frameratecounter;

			//prepara uma font para escrever no ecra
			CL_Font fnt_clansoft;
			fnt_clansoft = CL_Font(gc, L"Tahoma", 32);

			// Run until someone presses escape
			int i = 0;
			while (!quit)
			{
				unsigned startTime = CL_System::get_time();

				// Clear the display in a dark blue nuance
				// The four arguments are red, green, blue and alpha
				gc.clear(CL_Colorf(0.0f,0.0f,0.3f));

				//desenha o screen actual do screenmanager(nivel e/ou menu)
				sm->drawCurrentScreen();

				CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
				fnt_clansoft.draw_text(gc, 20, 30, fps);

				// Flip the display, showing on the screen what we have drawed
				// since last call to flip()
				window.flip(1);

				// This call processes user input and other events
				CL_KeepAlive::process(0);

				//proximo passo da logica e input output
				sm->handleEvents();

				unsigned drawTime = CL_System::get_time() - startTime;
				if(DESIRED_FRAME_TIME > drawTime)
					CL_System::sleep( DESIRED_FRAME_TIME - drawTime );
				
				frameratecounter.frame_shown();
			

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

/// The window was closed
void App::on_window_close()
{
	quit = true;
}
