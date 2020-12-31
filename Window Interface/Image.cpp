#include "Image.h"

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include <vector>

struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoord;
};

static const std::vector<Vertex> g_vertices{
	Vertex{ glm::vec3(-1,-1,0), glm::vec2(0,0) },
	Vertex{ glm::vec3(1,-1,0), glm::vec2(1,0) },
	Vertex{ glm::vec3(1,1,0), glm::vec2(1,1) },
	Vertex{ glm::vec3(-1,1,0), glm::vec2(0,1) }
};

static const std::vector<GLuint> g_indices{
	0, 1, 2, 2, 3, 0
};

static GLuint VAO = 0;
static GLuint VBO = 0;
static GLuint EBO = 0;

Image::Image() {

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

void Image::draw() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)g_indices.size(), GL_UNSIGNED_INT, 0);

}