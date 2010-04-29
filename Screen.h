#pragma once
#include <ClanLib/core.h>
#include <ClanLib/display.h>

class Screen
{
public:
	Screen(void);
	virtual ~Screen(void);
	virtual void draw();
	virtual void HandleEvents();
	virtual void on_input_down(const CL_InputEvent &key, const CL_InputState &state);
private:
	//TODO: estrutura com elementos do screen ou não e deixar isso numa subclasse

};
