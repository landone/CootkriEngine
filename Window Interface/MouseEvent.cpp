#include "MouseEvent.h"

MouseMotionEvent::MouseMotionEvent(int x, int y, int xr, int yr) : Event(EVENTTYPE::MOUSEMOTION) {

	pos[0] = x;
	pos[1] = y;
	rel[0] = xr;
	rel[1] = yr;

}

MouseButtonEvent::MouseButtonEvent(int x, int y, bool p, int b) : Event(EVENTTYPE::MOUSEBUTTON) {

	pos[0] = x;
	pos[1] = y;
	press = p;
	btn = (MOUSEBUTTON)b;

}