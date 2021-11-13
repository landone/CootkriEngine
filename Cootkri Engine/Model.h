#pragma once

#include "Component.h"
#include <Drawable.h>
#include <Mesh.h>

#include <string>

class Model : public Component, public Drawable {
public:

	Model(std::string path);

	void draw(void*) override;

private:

	Mesh mesh;

};