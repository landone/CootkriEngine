#include "Texture.h"

#include "stb_image.h"

#include <GL/glew.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static const unsigned int BMP_HEADER_SIZE = 14;

Texture::Texture() {

	//Do nothing

}

Texture::Texture(const std::string& path) {

	int numComp;
	int width, height;
	unsigned char* imageData = stbi_load(path.c_str(), &width, &height, &numComp, 4);
	if (imageData == nullptr) {
		printf("Texture failed to create: \"%s\"\n", path.c_str());
		return;
	}
	createTexture(imageData, width, height);
	stbi_image_free(imageData);

}

Texture::Texture(const unsigned char* buffer, int len) {
	loadFromMemory(buffer, len);
}

bool Texture::loadFromMemory(const unsigned char* buffer, int len) {

	int numComp;
	int width, height;
	unsigned char* imageData = stbi_load_from_memory(buffer, len, &width, &height, &numComp, 3);
	if (imageData == nullptr) {
		printf("Texture failed to create from memory: %s\n", stbi_failure_reason());
		return false;
	}
	createTexture(imageData, width, height);
	stbi_image_free(imageData);
	return true;
}

bool Texture::loadBMP(unsigned int rscID) {

	bool result;
	HRSRC hRes = FindResourceA(NULL, MAKEINTRESOURCEA(rscID), MAKEINTRESOURCEA(RT_BITMAP));
	if (hRes) {
		HGLOBAL hData = LoadResource(0, hRes);
		if (hData) {
			DWORD rawSize = SizeofResource(0, hRes);
			unsigned int dataSize = rawSize + BMP_HEADER_SIZE;
			unsigned char* raw = (unsigned char*)LockResource(hData);
			//VS Resources are garbage so I have to manually add BMP header
			unsigned char* data = new unsigned char[dataSize];
			data[0] = 'B';
			data[1] = 'M';
			*((int*)(&data[2])) = dataSize;
			data[6] = '\0';
			data[7] = '\0';
			data[8] = '\0';
			data[9] = '\0';
			*((int*)(&data[10])) = 54;
			memcpy(&data[BMP_HEADER_SIZE], raw, rawSize);
			result = loadFromMemory(data, dataSize);
			delete[] data;
		}
		else {
			printf("Unable to load mono image resource\n");
			return false;
		}
	}
	else {
		printf("Unable to find mono image resource\n");
		return false;
	}

	return result;

}

void Texture::bind(unsigned int index) {

	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, id);

}

glm::vec2 Texture::getDimensions() {
	
	return dimensions;

}

void Texture::createTexture(unsigned char* imageData, int width, int height) {

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

	dimensions[0] = (float)width;
	dimensions[1] = (float)height;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//Repeat texture when out-of-bounds
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Linearly interpolate only 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

}