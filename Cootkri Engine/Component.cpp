#include "Component.h"

#include <map>

static std::map<std::string, std::list<Component*>> componentMap;

Entity* Component::getEntity() {

	return ent;

}

Transform* Component::getTrans() {

	if (!ent) {
		return nullptr;
	}

	return &ent->getTrans();

}

std::vector<Component*> Component::findComponentsByName(std::string className) {

	if (componentMap.find(className) == componentMap.end()) {
		return std::vector<Component*>();
	}

	std::list<Component*>& list = componentMap[className];
	return std::vector<Component*> {std::begin(list), std::end(list)};

}

Component::Component(std::string className) {

	key = className;
	componentMap[key].push_back(this);

}

Component::~Component() {

	if (ent != nullptr) {
		ent->removeComponent(*this);
	}

	std::list<Component*>& list = componentMap[key];
	for (auto it = list.begin(); it != list.end(); ++it) {
		if ((*it) == this) {
			list.erase(it);
			break;
		}
	}

}