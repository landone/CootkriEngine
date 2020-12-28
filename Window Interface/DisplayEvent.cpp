#include "DisplayEvent.h"

DisplayFrameEvent::DisplayFrameEvent(float d) : Event(EVENTTYPE::DISPLAY_FRAME) {
	delta = d;
}

DisplayResizeEvent::DisplayResizeEvent(int w, int h) : Event(EVENTTYPE::DISPLAY_RESIZE) {
	size[0] = w;
	size[1] = h;
}