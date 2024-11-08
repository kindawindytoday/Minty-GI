#pragma once

#include "../Misc/Singleton.h"
#include "../Misc/ResourceLoader.h"
#include "InitGUI.h"
#include <Windows.h>
#include <d3d11.h>
#include <map>

struct Image {
	void* data = 0;
	DWORD sz = 0;
	ID3D11ShaderResourceView* srv = 0;
	int width, height = 0;
};

class ImageLoader : public Singleton<ImageLoader> {
public:
	std::map<int, Image> ImagesMap;
	void AddImage(int resourceNum);
};