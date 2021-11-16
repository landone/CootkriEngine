#pragma once

#include <string>
#include <vector>
#include "Texture.h"
#include "ObjectLoader.h"

class Mesh {
public:

	Mesh() {}
	~Mesh();

	bool Load(std::string path);
	void draw();

private:

	unsigned int VAO = 0;
	unsigned int VBO = 0;
	std::vector<ObjectLoader::Vertex> vertices;
	std::vector<ObjectLoader::Object> objects;
	std::vector<unsigned int> EBOs;

	void setupMesh();
	void deleteBuffers();

};