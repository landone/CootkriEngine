#include "MouseEvent.h"

MouseMotionEvent::MouseMotionEvent(glm::vec2 pt, int xr, int yr) : Event(EVENTTYPE::MOUSE_MOTION) {

	pos = pt;
	rel[0] = xr;
	rel[1] = yr;

}

MouseButtonEvent::MouseButtonEvent(glm::vec2 pt, bool p, int b) : Event(EVENTTYPE::MOUSE_BUTTON) {

	pos = pt;
	press = p;
	btn = (MOUSEBUTTON)b;

}