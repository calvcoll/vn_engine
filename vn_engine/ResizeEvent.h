#ifndef RESIZE_EVENT_H
#define RESIZE_EVENT_H

#include "Event.h"
class ResizeEvent :
	public Event
{
public:
	ResizeEvent(int, int, int, int);
	~ResizeEvent();

	int old_width;
	int old_height;
	int new_width;
	int new_height;
};

#endif