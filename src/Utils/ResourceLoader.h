#pragma once

#include "Singleton.h"
#include <Windows.h>
#include <iostream>

class ResourceLoader : public Singleton<ResourceLoader> {
public:
	bool LoadResourceToMemory(const char* resourceName, const char* resourceType, void*& dataOut, DWORD& sizeOut);
	void SetHandle(HMODULE handle);
private:
	HMODULE handle;
};