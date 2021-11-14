#pragma once

#include "Entity.h"

class Entity;

class Component : public Drawable {
public:

	~Component();

	Entity* getEntity();

	Transform* getTrans();

	virtual void draw(void*) override {}

protected:

	virtual void onAdd() {}

	virtual void onRemove() {}

	bool isDrawable = false;

private:

	friend Entity;
	Entity* ent;

};