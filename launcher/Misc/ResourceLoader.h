#pragma once

#include <Windows.h>
#include "../resource.h"
#include "Singleton.h"

class ResourceLoader : public Singleton<ResourceLoader> {
public:
	bool LoadResourceToMemory(const char* resourceName, const char* resourceType, void*& dataOut, DWORD& sizeOut);
	void SetHandle(HMODULE handle);

private:
	HMODULE handle;
};