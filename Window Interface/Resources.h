#pragma once

#include <string>

//Allocate and load a file into a memory. Must be deleted.
char* LoadResource(const char* path, int* size = nullptr);

//Load a text file into memory. String object returned.
std::string LoadTextFile(const char* path);