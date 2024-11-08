#include "ImageLoader.h"

void ImageLoader::AddImage(int resourceNum) {
	Image image;

	image.srv = 0;
	image.sz = 0;
	image.width = 0;
	image.height = 0;
	image.data = 0;

	if (!ResourceLoader::Instance().LoadResourceToMemory(MAKEINTRESOURCEA(resourceNum), "PNG", image.data, image.sz)) {
		printf("LoadResourceToMemory ERR! (image #%i)\n", resourceNum);
		return;
	}
	if (!GUI::LoadTextureFromMemory(image.data, image.sz, &image.srv, &image.width, &image.height)) {
		printf("LoadTextureFromMemory ERR! (image #%i)\n", resourceNum);
		return;
	}

	this->ImagesMap[resourceNum] = image;
}
