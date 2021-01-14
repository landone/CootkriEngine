#include "Text.h"
#include "Shader.h"
#include "resource.h"
#include "UIShader.h"

#include <GL/glew.h>

static Texture* DEFAULT_FONT = nullptr;

Text::Text() {

	if (DEFAULT_FONT == nullptr) {

		DEFAULT_FONT = new Texture();
		DEFAULT_FONT->loadResource(IDB_FONT_ASCII);

	}

	buffer = Shader::createBuffer();
	texture.setID(Texture::createTexture());

}

Text::~Text() {

	Shader::deleteBuffer(buffer);
	Texture::deleteTexture(texture.getID());

}

void Text::setText(const std::string& str) {

	contents = str;
	drawText();

}

void Text::drawText() {

	//Remember previously bound buffer
	GLint prevBound = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevBound);

	UIShader& shader = UIShader::get();
	shader.bind();
	Texture& font = (*DEFAULT_FONT);

	//Prepare texture
	int len = contents.length();
	//Dimensions of a single character
	glm::vec2 dim = font.getDimensions() / 16.0f;
	texture.bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, dim.x * len, dim.y, 0, GL_RGBA, GL_FLOAT, NULL);

	//Remember original viewport dimensions
	font.bind();
	Transform trans;
	GLint origDims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, origDims);
	glViewport(0, 0, dim.x, dim.y);

	//Draw characters to texture
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < len; i++) {



	}

	glViewport(origDims[0], origDims[1], origDims[2], origDims[3]);

}