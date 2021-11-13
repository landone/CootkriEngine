#include "Entity.h"

Transform& Entity::getTrans() {

	return trans;

}

bool Entity::hasComponent(Component& input) {

	Component* target = &input;
	for (Component* comp : components) {
		if (comp == target) {
			return true;
		}
	}
	return false;

}

bool Entity::addComponent(Component& comp) {

	if (hasComponent(comp)) {
		return false;
	}

	components.push_back(&comp);
	comp.ent = this;
	comp.onAdd();
	return true;

}

bool Entity::removeComponent(Component& comp) {

	auto it = components.begin();
	for (; it != components.end(); ++it) {
		if ((*it) == &comp) {
			comp.onRemove();
			components.erase(it);
			comp.ent = nullptr;
			return true;
		}
	}
	return false;

}

void Entity::removeAllComponents() {

	auto it = components.begin();
	for (; it != components.end(); ++it) {
		(*it)->onRemove();
		(*it)->ent = nullptr;
	}
	components.clear();

}

Entity::~Entity() {

	removeAllComponents();

}