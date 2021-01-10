#include "Resources.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

unsigned char* LoadResource(unsigned int ID, int* size) {

	HRSRC hRes = FindResourceA(NULL, MAKEINTRESOURCEA(ID), MAKEINTRESOURCEA(RT_RCDATA));
	if (!hRes) {
		printf("Unable to find resource \"%d\"\n", ID);
		return nullptr;
	}
	HGLOBAL hData = LoadResource(NULL, hRes);
	if (!hData) {
		printf("Unable to load resource \"%d\"\n", ID);
		return nullptr;
	}
	if (size) {
		(*size) = SizeofResource(NULL, hRes);
	}
	return (unsigned char*)LockResource(hData);

}