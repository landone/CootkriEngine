#include "Component.h"

Entity* Component::getEntity() {

	return ent;

}

Transform* Component::getTrans() {

	if (!ent) {
		return nullptr;
	}

	return &ent->getTrans();

}

Component::~Component() {

	if (ent != nullptr) {
		ent->removeComponent(*this);
	}

}