#define _CRT_SECURE_NO_WARNINGS

#include "Resources.h"
#include <stdio.h>

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
	fseek(file, SEEK_SET, 0);
	fread(data, size, 1, file);
	fclose(file);

	if (returnSize) {
		(*returnSize) = size;
	}

	return data;

}