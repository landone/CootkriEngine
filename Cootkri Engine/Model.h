#pragma once

#include "Component.h"
#include <Drawable.h>
#include "Mesh.h"

#include <string>

class Model : public Component {
public:

	/// <summary>
	/// Load a model by pathway
	/// </summary>
	/// <param name="path"></param>
	Model(std::string path);

	/// <summary>
	/// Draw this model with a geometry shader
	/// </summary>
	/// <param name="geomShader"></param>
	void draw(void* geomShader) override;

private:

	Mesh mesh;

};