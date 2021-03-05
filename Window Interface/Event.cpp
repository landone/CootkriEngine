#include "Event.h"

Event::Event(EVENTTYPE t) {

	type = t;

}

EventListener::EventListener(EventManager* p) : EventListener() {

	setParent(p);

}

EventListener::~EventListener() {

	removeParent();

}

EventManager::~EventManager() {

	//Remove parent from all listeners
	std::map<EVENTTYPE, std::list<EventListener*>>::iterator it = listenerMap.begin();
	//Loop through event types
	while (it != listenerMap.end()) {

		std::list<EventListener*>& list = it->second;
		std::list<EventListener*>::iterator itt = list.begin();
		//Loop through listeners for that type
		while (itt != list.end()) {

			//Remove parent
			(*itt)->parent = nullptr;

			++itt;
		}

		++it;
	}

}

void EventManager::sendEvent(Event* e) {

	//If real event
	if (e) {
		//If there are listeners for this event
		if (listenerMap.find(e->type) != listenerMap.end()) {
			//Send event to all listeners for this type
			std::list<EventListener*>& list = listenerMap[e->type];
			std::list<EventListener*>::iterator it = list.begin();
			while (it != list.end()) {
				(*it)->onEvent(e);
				++it;
			}
		}
	}

}

void EventListener::setParent(EventManager* p) {

	//If parent already exists, remove it
	if (parent) {
		removeParent();
	}

	//If parent being set exists
	if (p) {
		parent = p;
		//Add self to parent's event lists
		std::set<EVENTTYPE>::iterator it = types.begin();
		while (it != types.end()) {
			parent->listenerMap[*it].push_back(this);
			++it;
		}
	}

}

EventManager* EventListener::getParent() {

	return parent;

}

void EventListener::removeParent() {

	//If parent exists
	if (parent) {

		std::set<EVENTTYPE>::iterator it = types.begin();
		//Loop through listened event types
		while (it != types.end()) {

			std::list<EventListener*>& list = parent->listenerMap[*it];
			std::list<EventListener*>::iterator itt = list.begin();
			//Remove self from parent's list
			while (itt != list.end()) {
				if ((*itt) == this) {
					list.erase(itt);
					break;
				}
				++itt;
			}

			++it;
		}

		//Forget parent
		parent = nullptr;

	}

}

void EventListener::addType(EVENTTYPE t) {
	//If not in set yet
	if (types.find(t) == types.end()) {
		types.insert(t);
		if (parent) {
			//Add self to parent's list
			parent->listenerMap[t].push_back(this);
		}
	}
}

void EventListener::removeType(EVENTTYPE t) {

	//If type in set (legitimate removal)
	if (types.find(t) != types.end()) {
		types.erase(t);
		if (parent) {
			//Remove self from parent's list
			std::list<EventListener*>& list = parent->listenerMap[t];
			std::list<EventListener*>::iterator it = list.begin();
			while (it != list.end()) {
				if ((*it) == this) {
					list.erase(it);
					break;
				}
				++it;
			}
		}
	}

}