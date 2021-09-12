#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

enum class MOUSEBUTTON {
	LEFT,
	MIDDLE,
	RIGHT
};

class MouseMotionEvent : public Event {
public:
	MouseMotionEvent(glm::vec2 pt, int xr, int yr);
	glm::vec2 pos;
	int rel[2];
};

class MouseButtonEvent : public Event {
public:
	MouseButtonEvent(glm::vec2 pt, bool press, int btn);
	glm::vec2 pos;
	bool press;
	MOUSEBUTTON btn;
};