#include "Mesh.h"
#include "ObjectLoader.h"

#include <GL/glew.h>
#include <fstream>
#include <map>
#include <iostream>

void Mesh::setupMesh() {

	if (VAO == NULL) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		//Each object has it's own EBO
		EBOs.resize(objects.size());
		glGenBuffers((GLsizei)objects.size(), &EBOs[0]);
	}

	//Prepare buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ObjectLoader::Vertex), &vertices[0], GL_DYNAMIC_DRAW);

	//Add mesh objects to element buffers
	for (int i = 0; i < EBOs.size(); ++i) {
		//Skip empty objects
		if (objects[i].indices.size() == 0) {
			continue;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, objects[i].indices.size() * sizeof(GLuint), &objects[i].indices[0], GL_STATIC_DRAW);
	}

	//Prepare attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ObjectLoader::Vertex), (GLvoid*)offsetof(ObjectLoader::Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ObjectLoader::Vertex), (GLvoid*)offsetof(ObjectLoader::Vertex, texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ObjectLoader::Vertex), (GLvoid*)offsetof(ObjectLoader::Vertex, normal));

	//Unbind array
	glBindVertexArray(0);
}

void Mesh::draw() {

	glBindVertexArray(VAO);
	//Draw each object w/ respective texture
	for (int i = 0; i < EBOs.size(); i++) {
		if (objects[i].indices.size() == 0) {
			continue;
		}
		objects[i].texture.bind();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
		glDrawElements(GL_TRIANGLES, (GLsizei)objects[i].indices.size(), GL_UNSIGNED_INT, 0);
	}

}

Mesh::~Mesh() {
	deleteBuffers();
}

void Mesh::deleteBuffers() {
	if (VAO != NULL) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers((GLsizei)EBOs.size(), &EBOs[0]);
	}
	VAO = NULL;
	VBO = NULL;
	EBOs.clear();
}


bool Mesh::Load(std::string path) {

	if (!ObjectLoader::LoadOBJ(path, objects, vertices)) {
		return false;
	}

	setupMesh();
	return true;

}