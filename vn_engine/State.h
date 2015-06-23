#ifndef STATE_H
#define STATE_H

class State
{
public:
	State();
	~State();
	virtual void render();
	virtual void update();
};

#endif
