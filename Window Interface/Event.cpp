#include "Event.h"

Event::Event(EVENTTYPE t) {

	type = t;

}

EventListener::EventListener(EventManager* p) {

	setParent(p);

}

EventListener::~EventListener() {

	removeParent();

}

EventManager::~EventManager() {

	//Remove parent from all listeners
	std::map<EVENTTYPE, std::list<EventListener*>>::iterator it = listenerMap.begin();
	while (it != listenerMap.end()) {

		std::list<EventListener*>& list = it->second;
		std::list<EventListener*>::iterator itt = list.begin();
		while (itt != list.end()) {

			(*itt)->parent = nullptr;

			++itt;
		}

		++it;
	}

}

void EventManager::sendEvent(Event* e) {

	if (e) {
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

	if (parent) {
		removeParent();
	}

	if (p) {
		parent = p;
		//Add self to listener list of event types on parent
		std::set<EVENTTYPE>::iterator it = types.begin();
		while (it != types.end()) {
			parent->listenerMap[*it].push_back(this);
			++it;
		}
	}

}

void EventListener::removeParent() {

	if (parent) {

		std::set<EVENTTYPE>::iterator it = types.begin();
		while (it != types.end()) {

			std::list<EventListener*>& list = parent->listenerMap[*it];
			std::list<EventListener*>::iterator itt = list.begin();
			while (itt != list.end()) {
				if ((*itt) == this) {
					list.erase(itt);
					break;
				}
				++itt;
			}

			++it;
		}

		parent = nullptr;

	}

}

void EventListener::addType(EVENTTYPE t) {
	//If already exists, do nothing
	if (types.find(t) == types.end()) {
		types.insert(t);
		if (parent) {
			//Add self to parent listener list
			parent->listenerMap[t].push_back(this);
		}
	}
}

void EventListener::removeType(EVENTTYPE t) {

	if (types.find(t) != types.end()) {
		types.erase(t);
		if (parent) {
			//Remove self from parent listener list
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