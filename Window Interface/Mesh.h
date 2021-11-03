#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include "Texture.h"

class Mesh {
public:

	Mesh() {}
	~Mesh();

	bool Load(std::string path);
	void draw();

private:

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
		float texID;
	};

	struct Object {
		std::string name;
		std::string material;
		std::vector<unsigned int> indices;
		unsigned int texIndex = 0;
	};

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	unsigned int EBO = 0;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Object> objects;
	std::vector<Texture> textures;

	void setupMesh();
	void deleteBuffers();

	/* Read MTL file, return vector of material name paired with pathway */
	std::vector<std::pair<std::string, std::string>> ProcessMTL(std::string path);

	void Init(std::vector<Mesh::Vertex> verts, std::vector<unsigned int> indices);

};