#pragma once

#include "resource.h"

//Load an embedded resource by ID. nullptr on failure
unsigned char* LoadResource(unsigned int ID, int* size = nullptr);