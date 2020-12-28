#pragma once

#include "Event.h"

class DisplayFrameEvent : public Event {
public:

	DisplayFrameEvent(float delta);
	float delta = 0.0f;

};

class DisplayResizeEvent : public Event {
public:

	DisplayResizeEvent(int w, int h);
	int size[2];

};