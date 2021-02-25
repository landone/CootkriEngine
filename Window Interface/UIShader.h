#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class UIShader : public Shader {
public:

	//Get global UI shader
	static UIShader& get();

	//Index of which active texture to use
	void setTextureIndex(unsigned int);
	//Transformation matrix
	void setTransMatrix(const glm::mat4&);
	//Tint draw color
	void setTint(const glm::vec3&);
	//Tint draw color
	void setTint(float r, float g, float b);
	//Offset or scale texture
	void setTexMod(float xOffs=0, float yOffs=0, float xScale=1, float yScale=1);
	//Set UI draw layer from 0 to 1. Smaller drawn on top
	void setLayer(float);

private:

	UIShader();

};