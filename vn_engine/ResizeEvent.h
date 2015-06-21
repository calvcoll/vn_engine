#ifndef RESIZE_EVENT_H
#define RESIZE_EVENT_H

#include "Event.h"
class ResizeEvent :
	public Event
{
public:
	ResizeEvent(int old_x, int old_y, int new_x, int new_y, double _scaleX, double _scaleY);
	~ResizeEvent();

	int old_width;
	int old_height;
	int new_width;
	int new_height;
	double scaleX;
	double scaleY;
};

#endif