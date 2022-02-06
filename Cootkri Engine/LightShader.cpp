#include "LightShader.h"
#include "Resources.h"

#include <GL/glew.h>

static const char* VERT_SHDR = "./shaders/LightShader.vs";
static const char* FRAG_SHDR = "./shaders/LightShader.fs";

static std::string vertexShader;
static std::string fragmentShader;

LightShader::LightShader() {

	if (vertexShader.empty()) {
		vertexShader = LoadTextFile(VERT_SHDR);
		fragmentShader = LoadTextFile(FRAG_SHDR);
	}

	load(vertexShader.c_str(), fragmentShader.c_str());

	createAttribute("position");
	createAttribute("texCoord");

	uniforms[POS_MAP] = createUniform("gPosition");
	uniforms[NORM_MAP] = createUniform("gNormal");
	uniforms[COLOR_MAP] = createUniform("gColor");
	uniforms[LIGHT_COLOR] = createUniform("lightColor");
	uniforms[LIGHT_POS] = createUniform("lightPos");
	uniforms[LIGHT_SIZE] = createUniform("lightSize");
	uniforms[CAM_POS] = createUniform("camPos");

}

void LightShader::setCameraPos(glm::vec3 pos) {

	bind(nullptr);
	glUniform3fv(uniforms[CAM_POS], 1, &pos[0]);

}

void LightShader::setMaps(unsigned int pos, unsigned int norm, unsigned int color) {

	maps[0] = pos;
	maps[1] = norm;
	maps[2] = color;
	glUniform1i(uniforms[POS_MAP], 0);
	glUniform1i(uniforms[NORM_MAP], 1);
	glUniform1i(uniforms[COLOR_MAP], 2);

}

void LightShader::bind(Renderer* renderer) {

	Shader::bind(renderer);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, maps[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, maps[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, maps[2]);
}

void LightShader::setLight(Light light) {

	Shader::bind(nullptr);

	Entity& ent = (*light.getEntity());
	glm::vec4 pos = glm::vec4(ent.getTrans().getPos(), light.getRange());
	glm::vec4 color = glm::vec4(light.getColor(), light.getIntensity());
	glUniform1i(uniforms[LIGHT_SIZE], 1);
	glUniform4fv(uniforms[LIGHT_POS], 1, &pos[0]);
	glUniform4fv(uniforms[LIGHT_COLOR], 1, &color[0]);

}