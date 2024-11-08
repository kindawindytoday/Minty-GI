#include "ResourceLoader.h"
#include <iostream>

bool ResourceLoader::LoadResourceToMemory(const char* resourceName, const char* resourceType, void*& dataOut, DWORD& sizeOut)
{
	//DISprintf("1\n");
	if (!this->handle) return false;
	//DISprintf("2\n");
	HRSRC resource = FindResourceA(this->handle, resourceName, resourceType);
	if (!resource) return false;
	//DISprintf("3\n");
	HGLOBAL hglobal = LoadResource(this->handle, resource);
	if (!hglobal) return false;
	//DISprintf("4\n");
	dataOut = LockResource(hglobal);
	sizeOut = SizeofResource(this->handle, resource);
	//DISprintf("5\n");
	if (dataOut && (sizeOut > 0)) return true;
	//DISprintf("6\n");
	return false;
}

void ResourceLoader::SetHandle(HMODULE handle)
{
	this->handle = handle;
}
