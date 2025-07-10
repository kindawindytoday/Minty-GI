#include "ResourceLoader.h"

bool ResourceLoader::LoadResourceToMemory(const char* resourceName, const char* resourceType, void*& dataOut, DWORD& sizeOut)
{
	if (!this->handle) return false;
	HRSRC resource = FindResourceA(this->handle, resourceName, resourceType);
	//printf("1: %i\n", GetLastError());
	if (!resource) return false;
	HGLOBAL hglobal = LoadResource(this->handle, resource);
	//printf("2: %i\n", GetLastError());
	if (!hglobal) return false;
	dataOut = LockResource(hglobal);
	sizeOut = SizeofResource(this->handle, resource);
	if (dataOut && (sizeOut > 0)) return true;
	return false;
}

void ResourceLoader::SetHandle(HMODULE handle)
{
	this->handle = handle;
}
