#include "Image.h"
#include "UIShader.h"
#include "MouseEvent.h"

#include <GL/glew.h>

#include <vector>

static Texture MONO_IMAGE;
static glm::vec2 DEFAULT_SIZE = glm::vec2(64, 64);
static unsigned char DEFAULT_COLOR[4] = { 255,255,255,255 };

typedef UIElement::Vertex Vertex;

static std::vector<std::vector<Vertex>> g_vertices;
static std::vector<unsigned int> g_indices;

static std::vector<GLuint> VAO;
static std::vector<GLuint> VBO;
static std::vector<GLuint> EBO;

Image::Image() {

	prepareVertexArray();

	//Monochromatic image not set yet
	if (MONO_IMAGE.getDimensions().x == 0) {
		MONO_IMAGE.setDimensions(glm::vec2(1, 1));
		MONO_IMAGE.createTexture((unsigned char*)&DEFAULT_COLOR[0], 1, 1);
	}

	texture = MONO_IMAGE;
	setSize(DEFAULT_SIZE);

}

Image::Image(const Texture& tex) : Image() {

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

void Image::draw(void* shd) {

	UIShader& shader = *(UIShader*)shd;
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

void Image::prepareVertexArray() {
	/* Initialize static variables if necessary */
	if (VAO.size() == 0) {

		g_indices = getIndices();

		/* Create meshes for all corners */
		for (int i = 0; i < (int)UIElement::ORIGIN::MAX_ORIGINS; ++i) {
			std::vector<Vertex> newVerts;
			const std::vector<Vertex>& defaultVerts = getVertices();
			glm::vec3 offs = getOriginOffset((UIElement::ORIGIN)i);
			for (int j = 0; j < defaultVerts.size(); ++j) {
				Vertex vert = defaultVerts[j];
				vert.position += offs;
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