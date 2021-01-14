#pragma once

#include "EventType.h"

#include <map>
#include <list>
#include <set>

class EventManager;

/*
* Basic event class for passing information to listener.
*/
class Event {
public:
	Event(EVENTTYPE);
	EVENTTYPE type;
};

/*
* Listener class for specific events from an event manager.
*/
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
	//Get parent whose being listened to
	EventManager* getParent();
	//Stop listening to parent
	void removeParent();
private:
	friend EventManager;
	EventManager* parent = nullptr;
	//Set of events currently being listened for.
	std::set<EVENTTYPE> types;
};

/*
* Class for sending events to all listeners.
*/
class EventManager {
public:
	~EventManager();
protected:
	//Send event to all listeners
	void sendEvent(Event*);
private:
	friend EventListener;
	//Map event type to list of listeners for fast event calling.
	std::map<EVENTTYPE, std::list<EventListener*>> listenerMap;

};