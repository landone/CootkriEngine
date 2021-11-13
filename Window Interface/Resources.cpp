#define _CRT_SECURE_NO_WARNINGS

#include "Resources.h"
#include <stdio.h>
#include <fstream>

char* LoadResource(const char* path, int* returnSize) {

	FILE* file = fopen(path, "rb");
	if (!file) {
		printf("Unable to open file \"%s\"\n", path);
		if (returnSize) {
			(*returnSize) = 0;
		}
		return nullptr;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	char* data = new char[size];
	fseek(file, 0, SEEK_SET);
	fread(data, size, 1, file);
	fclose(file);

	if (returnSize) {
		(*returnSize) = size;
	}

	return data;

}

std::string LoadTextFile(const char* path) {

	std::ifstream file;
	std::string output;
	file.open(path);
	if (!file.is_open()) {
		return output;
	}
	std::string line;
	while (std::getline(file, line)) {
		output += line + '\n';
	}

	return output;

}