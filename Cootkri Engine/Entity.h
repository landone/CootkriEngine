#pragma once

#include <Transform.h>
#include <list>

#include "Component.h"
class Component;

class Entity {
public:

	~Entity();

	bool addComponent(Component& comp);

	bool removeComponent(Component& comp);

	void removeAllComponents();

	bool hasComponent(Component& comp);

	Transform& getTrans();

private:

	Transform trans;
	std::list<Component*> components;

};