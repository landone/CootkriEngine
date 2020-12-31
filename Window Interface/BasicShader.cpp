#include "BasicShader.h"

#include <GL/glew.h>

const char* vertexShader =
"#version 400 core\n"
"layout (location = 0) in vec3 position;"
"layout (location = 1) in vec2 texCoord;"
"out vec2 TexCoords;"
"uniform mat4 transMatrix;"
"void main() {"
"	TexCoords = texCoord;"
"	gl_Position = transMatrix * vec4(position, 1.0);"
"}";

const char* fragmentShader =
"#version 400 core\n"
"in vec2 TexCoords;"
"out vec4 FragColor;"
"uniform sampler2D texMap;"
"uniform vec3 tint;"
"void main() {"
"	vec4 origColor = texture(texMap, TexCoords);"
"	if (origColor.a == 0.0f) {"
"		FragColor = vec4(tint, 1);"
"	} else {"
"		FragColor = vec4(origColor.xyz * tint, 1);"
"	}"
"}";

BasicShader::BasicShader() : Shader(vertexShader, fragmentShader) {

	createAttribute("position");
	createAttribute("texCoord");
	createUniform("transMatrix");
	createUniform("texMap");
	createUniform("tint");

	//Set default uniform values
	setTint(1, 1, 1);
	setTextureIndex(0);
	setTransMatrix(glm::mat4(1.0f));

}

void BasicShader::setTint(const glm::vec3& color) {

	bind();
	glUniform3fv(uniforms[2], 1, &color[0]);

}

void BasicShader::setTextureIndex(unsigned int ind) {

	bind();
	glUniform1ui(uniforms[1], ind);

}

void BasicShader::setTransMatrix(const glm::mat4& mat) {

	bind();
	glUniformMatrix4fv(uniforms[0], 1, GL_FALSE, &mat[0][0]);

}

void BasicShader::setTint(float r, float g, float b) {

	setTint(glm::vec3(r, g, b));

}