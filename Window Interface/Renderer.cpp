#include "Renderer.h"

#include <GL/glew.h>

Renderer::Renderer(Shader* shdr, unsigned int bufID) {

	shader = shdr;
	bufferID = bufID;

}

void Renderer::setShader(Shader* shd) {

	if (!shd) {
		return;
	}

	shader = shd;

}

void Renderer::setBuffer(unsigned int bufID) {

	bufferID = bufID;

}

unsigned int Renderer::makeBuffer() {

	bufferID = Shader::createBuffer();
	return bufferID;

}

unsigned int Renderer::getBuffer() {

	return bufferID;

}

void Renderer::setClearColor(glm::vec4 color) {

	clearColor = color;

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

	shader->bind();
	shader->bindBuffer(bufferID);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (Drawable* el : elemList) {
		el->draw(shader);
	}

}