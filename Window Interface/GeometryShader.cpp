#include "GeometryShader.h"
#include "Resources.h"

#include <GL/glew.h>

static const char* VERT_SHDR = "./shaders/GeometryShader.vs";
static const char* FRAG_SHDR = "./shaders/GeometryShader.fs";

static char* vertexShader = nullptr;
static char* fragmentShader = nullptr;

GeometryShader::GeometryShader() : Shader() {

	if (vertexShader == nullptr) {
		vertexShader = LoadResource(VERT_SHDR);
		fragmentShader = LoadResource(FRAG_SHDR);
	}

	load(vertexShader, fragmentShader);

	createAttribute("position");
	createAttribute("texCoord");
	createAttribute("normal");

	uniforms[TRANS_MAT] = createUniform("transMatrix");
	uniforms[ROT_MAT] = createUniform("rotMatrix");
	uniforms[VIEW_MAT] = createUniform("viewMatrix");
	uniforms[TEXTURES] = createUniform("textures");
	uniforms[TINT] = createUniform("tint");

	setTint(glm::vec3(1, 1, 1));

	/* Initialize sampler2D array uniform */
	GLint texIDs[MAX_TEXTURES];
	for (int i = 0; i < MAX_TEXTURES; i++) {
		texIDs[i] = i;
	}
	glUniform1iv(uniforms[TEXTURES], MAX_TEXTURES, &texIDs[0]);

}

void GeometryShader::setTransMatrix(const glm::mat4& mat) {

	bind(nullptr);
	glUniformMatrix4fv(uniforms[TRANS_MAT], 1, GL_FALSE, &mat[0][0]);

}

void GeometryShader::setRotationMatrix(const glm::mat4& mat) {

	bind(nullptr);
	glUniformMatrix4fv(uniforms[ROT_MAT], 1, GL_FALSE, &mat[0][0]);

}

void GeometryShader::setViewMatrix(const glm::mat4& mat) {

	bind(nullptr);
	glUniformMatrix4fv(uniforms[VIEW_MAT], 1, GL_FALSE, &mat[0][0]);

}

void GeometryShader::setTint(const glm::vec3& color) {

	bind(nullptr);
	glUniform3fv(uniforms[TINT], 1, &color[0]);

}