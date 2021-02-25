#include "Text.h"
#include "Shader.h"
#include "resource.h"
#include "UIShader.h"

#include <GL/glew.h>

static Texture* DEFAULT_FONT = nullptr;
static const float CHAR_LEN = 16.0f;
static const float CHAR_SZ = 1.0f / CHAR_LEN;

Text::Text() {

	if (DEFAULT_FONT == nullptr) {

		DEFAULT_FONT = new Texture();
		DEFAULT_FONT->loadResource(IDB_FONT_ASCII);

	}

	buffer = Shader::createBuffer();
	texture.setID(Texture::createTexture());

}

Text::Text(const std::string& text) : Text() {

	setText(text);

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

	UIShader& shader = UIShader::get();
	shader.bind();
	//Remember previously bound buffer
	GLuint prevBound = shader.getBuffer();
	//Remember original viewport dimensions
	GLint origDims[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, origDims);
	//Bind new buffer
	shader.bindBuffer(buffer);
	Texture& font = (*DEFAULT_FONT);

	//Prepare texture
	int len = contents.length();
	//Dimensions of the final text
	glm::vec2 dim = font.getDimensions() / CHAR_LEN;
	dim.x *= len;
	texture.bind();
	//texture.setDimensions(dim);
	texture.setDimensions(dim);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getID(), 0);

	font.bind();
	Transform trans;
	glViewport(0, 0, dim.x, dim.y);

	//Clear and restore original clear color
	GLfloat origClear[4];
	glGetFloatv(GL_COLOR_CLEAR_VALUE, origClear);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(origClear[0], origClear[1], origClear[2], origClear[3]);

	//Draw characters to texture
	shader.setTint(1, 1, 1);
	trans.setScale(glm::vec3(2.0f / len, 2, 1));
	for (int i = 0; i < len; i++) {

		char c = contents[i];
		//Select correct character from image
		shader.setTexMod((c % (int)CHAR_LEN) * CHAR_SZ, 1.0f - CHAR_SZ - (c / (int)CHAR_LEN) * CHAR_SZ, CHAR_SZ, CHAR_SZ);
		//Set position from left to right and adjust for centered mesh
		trans.setPos(glm::vec3(-1 + 2.0f * (i + 0.5f) / (float)len, 0, 0));
		//Draw
		shader.setTransMatrix(trans.getMatrix());
		Image::drawStatic();

	}

	//Restore buffer & dimensions
	shader.bindBuffer(prevBound);
	shader.setTexMod();
	glViewport(origDims[0], origDims[1], origDims[2], origDims[3]);

	setSize(dim);

}