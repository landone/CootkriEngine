#pragma once

#include <glm/vec2.hpp>
#include <string>

class Texture {
public:

	Texture();
	//Load texture from file
	Texture(const std::string& path);
	//Load texture from memory
	Texture(const unsigned char* buffer, int len);

	//Bind texture to an active texture index
	void bind(unsigned int index = 0);
	//Original dimensions of texture
	glm::vec2 getDimensions();

private:

	unsigned int id = 0;
	glm::vec2 dimensions = glm::vec2();
	void CreateTexture(unsigned char* imageData, int w, int h);

};