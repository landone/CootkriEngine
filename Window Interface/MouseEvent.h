#pragma once

#include "Event.h"

enum class MOUSEBUTTON {
	LEFT,
	MIDDLE,
	RIGHT
};

class MouseMotionEvent : public Event {
public:
	MouseMotionEvent(int x, int y, int xr, int yr);
	int pos[2];
	int rel[2];
};

class MouseButtonEvent : public Event {
public:
	MouseButtonEvent(int x, int y, bool press, int btn);
	int pos[2];
	bool press;
	MOUSEBUTTON btn;
};