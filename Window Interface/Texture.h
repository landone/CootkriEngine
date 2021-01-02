#pragma once

#include <glm/vec2.hpp>
#include <string>

class Texture {
public:

	Texture();
	Texture(const std::string& path);

	//Bind texture to an active texture index
	void bind(unsigned int index = 0);
	//Original dimensions of texture
	glm::vec2 getDimensions();

private:

	unsigned int id = 0;
	glm::vec2 dimensions = glm::vec2();
	void CreateTexture(const std::string& path);

};