#pragma once

#include <Transform.h>
#include <list>
#include <Drawable.h>

#include "Component.h"
class Component;

class Entity : public Drawable {
public:

	~Entity();

	bool addComponent(Component& comp);

	bool removeComponent(Component& comp);

	void removeAllComponents();

	bool hasComponent(Component& comp);

	void draw(void*) override;

	void preDraw(void*) override;

	Transform& getTrans();

private:

	Transform trans;
	std::list<Component*> components;

};