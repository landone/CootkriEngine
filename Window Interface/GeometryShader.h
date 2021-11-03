#pragma once

#include "Shader.h"

class GeometryShader : public Shader {
public:

	GeometryShader();

	void setTransMatrix(const glm::mat4&);
	void setRotationMatrix(const glm::mat4&);
	void setViewMatrix(const glm::mat4&);
	void setTint(const glm::vec3& color);

private:

	enum UNIFORMS {
		TRANS_MAT = 0, ROT_MAT, VIEW_MAT,
		TEXTURES, TINT, MAX_UNIFORMS
	};
	unsigned int uniforms[(int)UNIFORMS::MAX_UNIFORMS];

	//Maximum textures that can be bound at once for drawing a model
	static const unsigned int MAX_TEXTURES = 16;

};