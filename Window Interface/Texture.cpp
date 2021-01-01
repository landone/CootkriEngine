#include "Texture.h"

#include "stb_image.h"

#include <GL/glew.h>

Texture::Texture() {



}

Texture::Texture(const std::string& path) {

	CreateTexture(path);

}

void Texture::bind(unsigned int index) {

	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, id);

}

glm::vec2 Texture::getDimensions() {
	
	return dimensions;

}

void Texture::CreateTexture(const std::string& path) {

	int numComp;
	int width, height;
	unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &numComp, 4);
	if (imageData == nullptr) {
		printf("Texture failed to create: \"%s\"\n", path.c_str());
		return;
	}

	/* Flip texture vertically to correct it */
	for (int i = 0; i < height / 2; i++) {
		for (int j = 0; j < width; j++) {
			int invI = height - 1 - i;
			unsigned char buf;

			buf = imageData[4 * (i * width + j)];
			imageData[4 * (i * width + j)] = imageData[4 * (invI * width + j)];
			imageData[4 * (invI * width + j)] = buf;

			buf = imageData[4 * (i * width + j) + 1];
			imageData[4 * (i * width + j) + 1] = imageData[4 * (invI * width + j) + 1];
			imageData[4 * (invI * width + j) + 1] = buf;

			buf = imageData[4 * (i * width + j) + 2];
			imageData[4 * (i * width + j) + 2] = imageData[4 * (invI * width + j) + 2];
			imageData[4 * (invI * width + j) + 2] = buf;

			buf = imageData[4 * (i * width + j) + 3];
			imageData[4 * (i * width + j) + 3] = imageData[4 * (invI * width + j) + 3];
			imageData[4 * (invI * width + j) + 3] = buf;
		}
	}

	dimensions[0] = width;
	dimensions[1] = height;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//Repeat texture when out-of-bounds
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Linearly interpolate only 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);

}