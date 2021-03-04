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

	//Create a blank texture in OpenGL. Return texture ID.
	static unsigned int createTexture();
	//Remove texture ID from memory.
	static void deleteTexture(unsigned int id);

	//Bind texture to an active texture index
	void bind(unsigned int index = 0);
	//Set this texture object's GL texture ID
	void setID(unsigned int);
	//Set dimensions of texture, optional image data parameter
	void setDimensions(const glm::vec2&, unsigned char* = nullptr);
	//Current dimensions of texture
	glm::vec2 getDimensions();
	//Get OpenGL id for this texture
	unsigned int getID() { return id; }
	//Create texture with image data and dimensions
	void createTexture(unsigned char* imageData, int w, int h);

private:

	unsigned int id = 0;
	glm::vec2 dimensions = glm::vec2(0,0);
	//Load image from memory
	bool loadFromMemory(const unsigned char* buffer, int len);

};