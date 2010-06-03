/*
 * app.h
 *
 *  Created on: Apr 12, 2010
 *      Author: bgouveia
 */

#ifndef APP_H_
#define APP_H_

#include "ScreenManager.h"
#include <ClanLib/sound.h>

// This is the Application class (That is instantiated by the Program Class)
class App
{
public:
	int start(const std::vector<CL_String> &args);
private:
	void on_window_close();
private:
	bool quit;
	ScreenManager * sm;
};


#endif /* APP_H_ */
