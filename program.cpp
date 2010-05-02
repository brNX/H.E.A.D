/*
 * program.cpp
 *
 *  Created on: Apr 12, 2010
 *      Author: bgouveia
 */

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include <ClanLib/application.h>
#include <ClanLib/gl.h>
//#include <ClanLib/gl1.h>
//#include <ClanLib/gdi.h>

#include "program.h"
#include "app.h"

int Program::main(const std::vector<CL_String> &args)
{
	// Initialize ClanLib base components
	CL_SetupCore setup_core;

	// Initialize the ClanLib display component
	CL_SetupDisplay setup_display;

	// Initialize the OpenGL drivers
	CL_SetupGL setup_gl;
	//CL_SetupGL1 setup_gl;
	//CL_SetupGDI setup_gdi;

	// Start the Application
	App app;
	int retval = app.start(args);
	return retval;
}

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);
