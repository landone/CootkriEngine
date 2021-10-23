#include "Text.h"
#include "Shader.h"
#include "UIShader.h"
#include "Resources.h"
#include "Renderer.h"

#include <GL/glew.h>

static Texture* DEFAULT_FONT = nullptr;
static const char* DEFAULT_FONT_PATH = "./textures/ascii.png";
static const float CHAR_LEN = 16.0f;
static const float CHAR_SZ = 1.0f / CHAR_LEN;
static unsigned int buffer = 0;
static Renderer* textRender = nullptr;

Text::Text() {

	if (DEFAULT_FONT == nullptr) {

		int size = 0;
		char* fontImage = LoadResource(DEFAULT_FONT_PATH, &size);
		DEFAULT_FONT = new Texture((const unsigned char*)fontImage, size);
		delete[] fontImage;
		buffer = Shader::createBuffer();

	}

	texture.setID(Texture::createTexture());

}

Text::Text(const std::string& text) : Text() {

	setText(text);

}

Text::~Text() {

	Texture::deleteTexture(texture.getID());

}

void Text::setText(const std::string& str) {

	contents = str;
	drawText();

}

void Text::drawText() {

	if (textRender == nullptr) {
		textRender = new Renderer(&UIShader::get());
	}

	//Dimensions of the final text
	glm::vec2 dim = DEFAULT_FONT->getDimensions() / CHAR_LEN;
	dim.x *= contents.length();

	textRender->setClearColor(glm::vec4(1, 0, 0, 1));
	textRender->add((Drawable*)this);
	textRender->addTexture(texture);
	textRender->setSize(dim);
	textRender->draw(customDraw, this);
	textRender->removeTexture(texture);
	textRender->remove((Drawable*)this);

}

void Text::customDraw(Renderer* render, void* data) {

	Text& me = *(Text*)data;
	Texture& font = (*DEFAULT_FONT);
	int len = (int)me.contents.length();
	
	font.bind();
	Transform trans;
	UIShader& shader = *(UIShader*)render->getShader();
	shader.setViewMatrix(glm::mat4(1));

	shader.setTint(1, 1, 1);
	trans.setScale(glm::vec3(2.0f / len, 2, 1));
	for (int i = 0; i < len; ++i) {
		char c = me.contents[i];
		//Select correct character from image
		shader.setTexMod((c % (int)CHAR_LEN) * CHAR_SZ, 1.0f - CHAR_SZ - (c / (int)CHAR_LEN) * CHAR_SZ, CHAR_SZ, CHAR_SZ);
		//Set position from left to right and adjust for centered mesh
		trans.setPos(glm::vec3(-1 + 2.0f * (i + 0.5f) / (float)len, 0, 0));
		//Draw
		shader.setTransMatrix(trans.getMatrix());
		Image::drawStatic();
	}

	//Restore texture mod
	shader.setTexMod();

}