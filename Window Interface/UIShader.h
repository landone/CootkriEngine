#pragma once

#include "Shader.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class UIShader : public Shader {
public:

	UIShader();

	//Get global UI shader
	static UIShader& get();

	/// <summary>
	/// Prepare UIShader for use in a renderer.
	/// </summary>
	/// <param name="renderer"></param>
	void bind(Renderer*) override;

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
	void setViewMatrix(const glm::mat4&);
	glm::mat4 getViewMatrix();

private:

	//Update view matrix with display size
	void updateViewMatrix(glm::vec2 winSize);

	glm::mat4 viewMat;

};