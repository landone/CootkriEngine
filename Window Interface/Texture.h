#pragma once

#include <glm/vec2.hpp>
#include <string>

class Texture {
public:

	Texture();
	Texture(const std::string& path);

	void bind(unsigned int index = 0);
	glm::vec2 getDimensions();

private:

	unsigned int id = 0;
	glm::vec2 dimensions = glm::vec2();
	void CreateTexture(const std::string& path);

};