#pragma once

class LevelManager
{
public:
	static LevelManager * getInstance();
private:
	static LevelManager * lm_instance;
};
