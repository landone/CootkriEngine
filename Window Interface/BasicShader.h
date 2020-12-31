#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class BasicShader : public Shader {
public:

	BasicShader();

	void setTextureIndex(unsigned int);
	void setTransMatrix(const glm::mat4&);
	void setTint(const glm::vec3&);
	void setTint(float r, float g, float b);

private:

	

};