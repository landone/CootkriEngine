#pragma once

#include "EventType.h"

#include <map>
#include <list>
#include <set>

class EventManager;

class Event {
public:
	Event(EVENTTYPE);
	EVENTTYPE type;
};

//Class for listening to specific event types from specific sources
class EventListener {
public:
	EventListener() {}
	EventListener(EventManager*);
	~EventListener();
protected:
	//Add a type of event to listen for
	void addType(EVENTTYPE);
	//Remove a type of event to listen for
	void removeType(EVENTTYPE);
	//Called when an event fires
	virtual void onEvent(Event*) = 0;
	//Set parent to listen for
	void setParent(EventManager*);
	//Stop listening to parent
	void removeParent();
private:
	friend EventManager;
	EventManager* parent = nullptr;
	std::set<EVENTTYPE> types;
};

class EventManager {
public:
	~EventManager();
protected:
	//Send event to all listeners
	void sendEvent(Event*);
private:
	friend EventListener;
	//Map event types to list of listeners
	std::map<EVENTTYPE, std::list<EventListener*>> listenerMap;

};