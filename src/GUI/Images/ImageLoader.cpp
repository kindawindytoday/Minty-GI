#include "ImageLoader.h"

bool ImageLoader::LoadImageFromResources(int resourceNum)
{
	Image image;

	image.srv = 0;
	image.dataSize = 0;
	image.data = 0;
	image.width = 0;
	image.height = 0;

	if (!ResourceLoader::Instance().LoadResourceToMemory(MAKEINTRESOURCEA(resourceNum), "PNG", image.data, image.dataSize)) {
		printf("LoadResourceToMemory ERR! Image #%i\n", resourceNum);
		return false;
	}

	if (!DxHook::LoadTextureFromMemory(image.data, image.dataSize, &image.srv, &image.width, &image.height)) {
		printf("LoadTextureFromMemory ERR! (image #%i)\n", resourceNum);
		return false;
	}

	this->ImagesMap[resourceNum] = image;

	return true;
}
