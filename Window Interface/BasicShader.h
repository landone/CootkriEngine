#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class BasicShader : public Shader {
public:

	BasicShader();

	//Index of which active texture to use
	void setTextureIndex(unsigned int);
	//Transformation matrix
	void setTransMatrix(const glm::mat4&);
	//Tint draw color
	void setTint(const glm::vec3&);
	//Tint draw color
	void setTint(float r, float g, float b);

};