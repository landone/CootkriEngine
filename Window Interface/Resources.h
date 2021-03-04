#pragma once

//Allocate and load a file into a memory. Must be deleted.
char* LoadResource(const char* path, int* size = nullptr);