#include "Renderer.h"

#include "Display.h"
#include "DisplayEvent.h"

#include <GL/glew.h>

Renderer::Renderer(Shader* shdr, EventManager* parent, Display* disp) {

	//Default to main display
	if (disp == nullptr) {
		disp = Display::getMain();
	}
	display = disp;

	//Use display as parent if not specified
	if (parent == nullptr) {
		setSize(display->getSize());
		parent = display;
	}
	setParent(parent);
	addType(EVENTTYPE::DISPLAY_RESIZE);

	shader = shdr;

}

Renderer::~Renderer() {

	if (bufferID != 0) {
		glDeleteBuffers(1, &bufferID);
		for (Texture& tex : textures) {
			Texture::deleteTexture(tex.getID());
		}
		Texture::deleteTexture(depthTexture);
	}

}

unsigned int Renderer::addTexture() {

	Texture newTex;
	newTex.setID(Texture::createTexture());
	
	addTexture(newTex);

	return newTex.getID();

}

void Renderer::addTexture(Texture tex) {

	if (bufferID == 0) {
		makeBuffer();
	}

	shader->bind(nullptr);
	shader->bindBuffer(bufferID);
	tex.bind();
	tex.setDimensions(dimensions);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + textures.size(), GL_TEXTURE_2D, tex.getID(), 0);
	textures.push_back(tex);
	if (textureAttachments.size() < textures.size()) {
		textureAttachments.push_back(textureAttachments.size() + GL_COLOR_ATTACHMENT0);
	}

	glDrawBuffers(textures.size(), &textureAttachments[0]);

}

void Renderer::removeTexture(Texture target) {

	std::list<Texture>::iterator it;
	for (it = textures.begin(); it != textures.end(); ++it) {

		Texture& tex = (*it);
		if (tex.getID() == target.getID()) {
			textures.erase(it);
			break;
		}

	}

}

void Renderer::onEvent(Event* evt) {

	if (evt->type == EVENTTYPE::DISPLAY_RESIZE) {
		DisplayResizeEvent& dispEvt = *(DisplayResizeEvent*)evt;
		setSize(glm::vec2((float)dispEvt.size[0], (float)dispEvt.size[1]));
	}

}

void Renderer::setShader(Shader* shd) {

	if (!shd) {
		return;
	}

	shader = shd;

}

unsigned int Renderer::makeBuffer() {

	bufferID = Shader::createBuffer();
	shader->bindBuffer(bufferID);

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, dimensions.x, dimensions.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	return bufferID;

}

void Renderer::setClearColor(glm::vec4 color) {

	clearColor = color;

}

void Renderer::setSize(glm::vec2 size) {

	dimensions = size;
	for (Texture& tex : textures) {
		tex.bind();
		tex.setDimensions(size);
	}

	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, size.x, size.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

}

glm::vec2 Renderer::getSize() {

	return dimensions;

}

Shader* Renderer::getShader() {

	return shader;

}

glm::vec2 Renderer::makeScreenCoords(glm::vec2 rel, glm::vec2 abs) {

	glm::vec2 size = getSize();
	glm::vec2 screenSpace = glm::vec2(size.x / size.y, 1.0f);
	glm::vec2 pxToScreen = display->getPixelToScreen();
	return (rel * screenSpace + abs * pxToScreen);

}

void Renderer::add(UIElement* elem) {

	if (!elem) {
		return;
	}

	elem->setRenderer(this);
	add((Drawable*)elem);

}

void Renderer::remove(UIElement* elem) {

	if (!elem) {
		return;
	}

	elem->setRenderer(nullptr);
	remove((Drawable*)elem);

}

void Renderer::add(Drawable* drawable) {

	if (!drawable) {
		return;
	}

	elemList.push_front(drawable);

}

void Renderer::remove(Drawable* drawable) {
	
	if (!drawable) {
		return;
	}

	elemList.remove(drawable);

}

void Renderer::draw() {

	prepareToDraw();

	for (Drawable* el : elemList) {
		el->draw(shader);
	}

}

void Renderer::draw(void(*func)(Renderer*,void*), void* data) {

	prepareToDraw();

	for (Drawable* el : elemList) {
		func(this,(void*)el);
	}

}

void Renderer::prepareToDraw() {

	shader->bind(this);
	shader->bindBuffer(bufferID);

	glViewport(0, 0, (GLsizei)dimensions.x, (GLsizei)dimensions.y);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}