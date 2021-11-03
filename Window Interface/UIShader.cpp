#include "UIShader.h"
#include "Resources.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "Display.h"
#include "DisplayEvent.h"

static UIShader* global = nullptr;
static const char* VERT_SHDR = "./shaders/UIShader.vs";
static const char* FRAG_SHDR = "./shaders/UIShader.fs";

static char* vertexShader = nullptr;
static char* fragmentShader = nullptr;

UIShader& UIShader::get() {

	if (global == nullptr) {
		global = new UIShader();
	}

	return (*global);

}

UIShader::UIShader() {

	//Instantiate shader strings
	if (vertexShader == nullptr) {
		vertexShader = LoadResource(VERT_SHDR);
		fragmentShader = LoadResource(FRAG_SHDR);
	}

	load(vertexShader, fragmentShader);

	createAttribute("position");
	createAttribute("texCoord");

	createUniform("transMatrix");
	createUniform("texMap");
	createUniform("tint");
	createUniform("texMod");
	createUniform("viewMatrix");

	//Set default uniform values
	setTint(1, 1, 1);
	setTextureIndex(0);
	setTransMatrix(glm::mat4(1.0f));
	setTexMod();

}

void UIShader::setTint(const glm::vec3& color) {

	bind(nullptr);
	glUniform3fv(uniforms[2], 1, &color[0]);

}

void UIShader::setTexMod(float xOffs, float yOffs, float xScale, float yScale) {

	bind(nullptr);
	glm::vec4 mod = glm::vec4(xOffs, yOffs, xScale, yScale);
	glUniform4fv(uniforms[3], 1, &mod[0]);

}

void UIShader::setTextureIndex(unsigned int ind) {

	bind(nullptr);
	glUniform1ui(uniforms[1], ind);

}

void UIShader::setTransMatrix(const glm::mat4& mat) {

	bind(nullptr);
	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &mat[0][0]);

}

void UIShader::setTint(float r, float g, float b) {

	setTint(glm::vec3(r, g, b));

}

void UIShader::setViewMatrix(const glm::mat4& viewMat) {

	bind(nullptr);
	glUniformMatrix4fv(uniforms[4], 1, GL_FALSE, &viewMat[0][0]);
	this->viewMat = viewMat;

}

glm::mat4 UIShader::getViewMatrix() {

	return viewMat;

}

void UIShader::bind(Renderer* render) {

	Shader::bind(render);

	if (render != nullptr) {

		updateViewMatrix(render->getSize());

	}

}

void UIShader::updateViewMatrix(glm::vec2 winSize) {

	float aspect = winSize.x / winSize.y;
	static const float fov = atan(1.0f) * 2;
	static const float near = 0.9f;
	static const float far = 1.1f;
	static const glm::mat4 lookAtMat = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 viewMat = glm::perspective(fov, aspect, near, far) * lookAtMat;
	setViewMatrix(viewMat);

}