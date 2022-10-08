#pragma once

#include "Entity.h"
#include <string>
#include <vector>

class Entity;

class Component : public Drawable {
public:

	Component(std::string className);
	~Component();

	Entity* getEntity();

	Transform* getTrans();

	virtual void draw(void*) override {}

	static std::vector<Component*> findComponentsByName(std::string);

	virtual std::string getClassname() = 0;

protected:

	virtual void onAdd() {}

	virtual void onRemove() {}

	bool isDrawable = false;

private:

	friend Entity;
	Entity* ent = nullptr;
	std::string key;

};