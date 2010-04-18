#pragma once
#include "Screen.h"

class Level :
	public Screen
{
public:
	Level(void);
	~Level(void);
	void draw();
	void HandleEvents();
};
