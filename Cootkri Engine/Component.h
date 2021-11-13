#pragma once

#include "Entity.h"

class Entity;

class Component {
public:

	~Component();

	Entity* getEntity();

	Transform* getTrans();

protected:

	virtual void onAdd() {}

	virtual void onRemove() {}

private:

	friend Entity;
	Entity* ent;

};