#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
class MenuState :
	public State
{
public:
	MenuState();
	~MenuState();
	void render();
	void update();
};

#endif