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

static std::vector<std::vector<Vertex>> g_vertices{
	{//Center
		Vertex{ glm::vec3(-0.5f,-0.5f,0), glm::vec2(0,0) },
		Vertex{ glm::vec3(0.5f,-0.5f,0), glm::vec2(1,0) },
		Vertex{ glm::vec3(0.5f,0.5f,0), glm::vec2(1,1) },
		Vertex{ glm::vec3(-0.5f,0.5f,0), glm::vec2(0,1) }
	}
};

static const std::vector<GLuint> g_indices{
	0, 1, 2, 2, 3, 0
};

static std::vector<GLuint> VAO;
static std::vector<GLuint> VBO;
static std::vector<GLuint> EBO;

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

ORIGIN Image::getOrigin() {
	return origin;
}

void Image::setOrigin(ORIGIN ori) {

	origin = ori;

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
	glBindVertexArray(VAO[(int)origin]);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

}

void Image::drawStatic() {

	glBindVertexArray(VAO[(int)ORIGIN::CENTER]);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

}

void prepareVertexArray() {
	if (VAO.size() == 0) {

		const glm::vec3 offsets[] = {
			glm::vec3(0,-0.5f,0),//Top
			glm::vec3(0,0.5f,0),//Bottom
			glm::vec3(-0.5f,0,0),//Right
			glm::vec3(0.5f,0,0),//Left
			glm::vec3(-0.5f,-0.5f,0),//TopRight
			glm::vec3(-0.5f,0.5f,0),//BottomRight
			glm::vec3(0.5f,-0.5f,0),//TopLeft
			glm::vec3(0.5f,0.5f,0),//BottomLeft
		};

		/* Create meshes for all corners */
		for (int i = 0; i < (int)ORIGIN::MAX_ORIGINS; ++i) {
			std::vector<Vertex> newVerts;
			for (int j = 0; j < g_vertices[0].size(); ++j) {
				Vertex vert = g_vertices[0][j];
				vert.position += offsets[i];
				newVerts.push_back(vert);
			}
			g_vertices.push_back(newVerts);
		}

		VAO.resize(g_vertices.size());
		VBO.resize(g_vertices.size());
		EBO.resize(g_vertices.size());
		for (int i = 0; i < g_vertices.size(); ++i) {
			glGenVertexArrays(1, &VAO[i]);
			glGenBuffers(1, &VBO[i]);
			glGenBuffers(1, &EBO[i]);

			glBindVertexArray(VAO[i]);

			glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
			glBufferData(GL_ARRAY_BUFFER, g_vertices[i].size() * sizeof(Vertex), &g_vertices[i][0], GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_indices.size() * sizeof(GLuint), &g_indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
		}

	}
}