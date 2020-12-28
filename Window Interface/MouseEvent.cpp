#include "MouseEvent.h"

MouseMotionEvent::MouseMotionEvent(int x, int y, int xr, int yr) : Event(EVENTTYPE::MOUSE_MOTION) {

	pos[0] = x;
	pos[1] = y;
	rel[0] = xr;
	rel[1] = yr;

}

MouseButtonEvent::MouseButtonEvent(int x, int y, bool p, int b) : Event(EVENTTYPE::MOUSE_BUTTON) {

	pos[0] = x;
	pos[1] = y;
	press = p;
	btn = (MOUSEBUTTON)b;

}