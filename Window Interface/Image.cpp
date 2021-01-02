#include "Image.h"
#include "DisplayEvent.h"
#include "UIShader.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoord;
};

static const std::vector<Vertex> g_vertices{
	Vertex{ glm::vec3(-0.5f,-0.5f,0), glm::vec2(0,0) },
	Vertex{ glm::vec3(0.5f,-0.5f,0), glm::vec2(1,0) },
	Vertex{ glm::vec3(0.5f,0.5f,0), glm::vec2(1,1) },
	Vertex{ glm::vec3(-0.5f,0.5f,0), glm::vec2(0,1) }
};

static const std::vector<GLuint> g_indices{
	0, 1, 2, 2, 3, 0
};

static GLuint VAO = 0;
static GLuint VBO = 0;
static GLuint EBO = 0;

void prepareVertexArray();

Image::Image(const Texture& tex, Display* d) {

	if (d == nullptr) {
		d = Display::getMain();
	}
	setParent(d);
	addType(EVENTTYPE::DISPLAY_RESIZE);

	texture = tex;
	prepareVertexArray();

	setSize(texture.getDimensions());

}

void Image::onEvent(Event* e) {

	//Fix absolute coordinates on resize
	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	if (absPos != glm::vec2(0, 0)) {
		trans.setPos(glm::vec3(relPos + absPos * ratio, 0));
	}
	if (absSize != glm::vec2(0, 0)) {
		trans.setScale(glm::vec3(relSize + absSize * ratio, 1));
	}

}

void Image::setPos(const glm::vec2& p, bool rel) {

	if (rel) {
		relPos = p;
	}
	else {
		absPos = p;
	}

	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	trans.setPos(glm::vec3(relPos + absPos * ratio, 0));

}

void Image::setSize(const glm::vec2& p, bool rel) {

	if (rel) {
		relSize = p;
	}
	else {
		absSize = p;
	}

	glm::vec2 ratio = ((Display*)getParent())->getPixelToScreen();
	trans.setScale(glm::vec3(relSize + absSize * ratio, 1));

}

void Image::setRot(float p) {

	trans.setRot(glm::vec3(0, 0, p));

}

glm::vec2 Image::getPos(bool rel) {

	return (rel ? relPos : absPos);

}

glm::vec2 Image::getSize(bool rel) {

	return (rel ? relSize : absSize);

}

float Image::getRot() {

	return trans.getRot().z;

}

void Image::draw() {

	texture.bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

}

Texture Image::getTexture() {

	return texture;

}

glm::mat4 Image::getMatrix() {

	return trans.getMatrix();

}

void prepareVertexArray() {
	if (VAO == 0) {

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(Vertex), &g_vertices[0], GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_indices.size() * sizeof(GLuint), &g_indices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));

	}
}