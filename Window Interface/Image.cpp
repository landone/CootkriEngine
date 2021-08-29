#include "Image.h"
#include "UIShader.h"
#include "MouseEvent.h"

#include <GL/glew.h>

#include <vector>

static Texture MONO_IMAGE;
static glm::vec2 DEFAULT_SIZE = glm::vec2(64, 64);
static unsigned char DEFAULT_COLOR[4] = { 255,255,255,255 };

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

Image::Image(Display* d) : UIElement(d) {

	prepareVertexArray();

	//Monochromatic image not set yet
	if (MONO_IMAGE.getDimensions().x == 0) {
		MONO_IMAGE.setDimensions(glm::vec2(1, 1));
		MONO_IMAGE.createTexture((unsigned char*)&DEFAULT_COLOR[0], 1, 1);
	}

	texture = MONO_IMAGE;
	setSize(DEFAULT_SIZE);

	addType(EVENTTYPE::MOUSE_BUTTON);

}

void Image::onEvent(Event* e) {

	UIElement::onEvent(e);

	if (e->type == EVENTTYPE::MOUSE_BUTTON) {
		MouseButtonEvent& me = *((MouseButtonEvent*)e);
		if (me.btn == MOUSEBUTTON::LEFT && !me.press) {
			/*if (collides(glm::vec2(me.pos[0], me.pos[1]))) {
				tint = glm::vec3(1,1,1) - tint;
			}*/
		}
	}

}

Image::Image(const Texture& tex, Display* d) : Image(d) {

	texture = tex;
	setSize(texture.getDimensions());

}

void Image::setTint(glm::vec3 t) {

	tint = t;

}

void Image::setTexture(const Texture& t) {

	texture = t;

}

glm::vec3 Image::getTint() {

	return tint;

}

Texture Image::getTexture() {

	return texture;

}

void Image::draw() {

	UIShader& shader = UIShader::get();
	shader.setTint(tint);
	shader.setTransMatrix(getMatrix());
	texture.bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

}

void Image::drawStatic() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

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