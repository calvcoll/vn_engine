#include "ResizeEvent.h"

ResizeEvent::ResizeEvent(int old_x, int old_y, int new_x, int new_y, double _scaleX, double _scaleY)
{
	old_width = old_x;
	old_height = old_y;
	new_width = new_x;
	new_height = new_y;
	scaleX = _scaleX;
	scaleY = _scaleY;
}


ResizeEvent::~ResizeEvent()
{
}
