#pragma once

class Screen
{
public:
	Screen(void);
	virtual ~Screen(void);
	virtual void draw();
	virtual void HandleEvents();
private:
	//TODO: estrutura com elementos do screen ou n�o e deixar isso numa subclasse

};
