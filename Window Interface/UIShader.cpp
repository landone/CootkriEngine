#include "UIShader.h"
#include "Resources.h"

#include <GL/glew.h>

static UIShader* global = nullptr;

char* vertexShader = nullptr;
char* fragmentShader = nullptr;

UIShader& UIShader::get() {

	if (global == nullptr) {
		global = new UIShader();
	}

	return (*global);

}

UIShader::UIShader() {

	//Instantiate shader strings
	if (vertexShader == nullptr) {
		vertexShader = (char*)LoadResource(IDB_UISHADER_VS);
		fragmentShader = (char*)LoadResource(IDB_UISHADER_FS);
	}

	load(vertexShader, fragmentShader);

	createAttribute("position");
	createAttribute("texCoord");
	createUniform("transMatrix");
	createUniform("texMap");
	createUniform("tint");
	createUniform("layer");
	createUniform("texMod");

	//Set default uniform values
	setTint(1, 1, 1);
	setTextureIndex(0);
	setTransMatrix(glm::mat4(1.0f));
	setTexMod();

}

void UIShader::setLayer(float l) {
	
	bind();
	//Set layers between -1 and 0 because exactly 1 is out of visibility
	glUniform1f(uniforms[3], glm::clamp(l, 0.0f, 1.0f) - 1);

}

void UIShader::setTint(const glm::vec3& color) {

	bind();
	glUniform3fv(uniforms[2], 1, &color[0]);

}

void UIShader::setTexMod(float xOffs, float yOffs, float xScale, float yScale) {

	bind();
	glm::vec4 mod = glm::vec4(xOffs, yOffs, xScale, yScale);
	glUniform4fv(uniforms[4], 1, &mod[0]);

}

void UIShader::setTextureIndex(unsigned int ind) {

	bind();
	glUniform1ui(uniforms[1], ind);

}

void UIShader::setTransMatrix(const glm::mat4& mat) {

	bind();
	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &mat[0][0]);

}

void UIShader::setTint(float r, float g, float b) {

	setTint(glm::vec3(r, g, b));

}