

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <Box2D/Box2D.h>

#include "app.h"
#include "Wiimote_handler.h"
#include "framerate_counter.h"

//1000 por ser millisegundos
#define DESIRED_FRAME_TIME 1000.0/60.0


// The start of the Application
int App::start(const std::vector<CL_String> &args)
{
		quit = false;
		
		try
		{

			//codigo para antialiasing/multisampling
			CL_OpenGLWindowDescription desc;
			desc.set_title("H.E.A.D");
			desc.set_size( CL_Size(640, 480), false );
			desc.set_multisampling(4);
			CL_DisplayWindow window(desc);	

			// Connect the Window close event
			CL_Slot slot_quit = window.sig_window_close().connect(this, &App::on_window_close);

			// Connect a keyboard handler to on_key_up()
			CL_Slot slot_input_up = (window.get_ic().get_keyboard()).sig_key_up().connect(this, &App::on_input_up);

			// Get the graphic context
			CL_GraphicContext gc = window.get_gc();

			FramerateCounter frameratecounter;

			CL_Font fnt_clansoft;
			fnt_clansoft = CL_Font(gc, L"Tahoma", 32);

			//variaveis para o tamanho da janela
			//int tamanhoxmax=window.get_geometry().right-window.get_geometry().left;
			int tamanhoymax=window.get_geometry().bottom-window.get_geometry().top;

			// Run until someone presses escape
			int i = 0;
			while (!quit)
			{

				unsigned startTime = CL_System::get_time();

				// Clear the display in a dark blue nuance
				// The four arguments are red, green, blue and alpha
				gc.clear(CL_Colorf(0.0f,0.0f,0.2f));

				CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
				fnt_clansoft.draw_text(gc, 20, 30, fps);

				// Flip the display, showing on the screen what we have drawed
				// since last call to flip()
				window.flip(1);

				// This call processes user input and other events
				CL_KeepAlive::process(0);

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

// A key was pressed
void App::on_input_up(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_ESCAPE)
	{
		quit = true;
	}

	if(key.id == CL_KEY_UP){
	}

	if(key.id == CL_KEY_DOWN){
	}

	if(key.id == CL_KEY_LEFT){
	}

	if(key.id == CL_KEY_RIGHT){
	}
}

// The window was closed
void App::on_window_close()
{
	quit = true;
}
