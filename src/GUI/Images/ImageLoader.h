#pragma once

#include "../../Utils/ResourceLoader.h"
#include "../../Utils/Singleton.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../DirectX/DirectXHook.h"
#include <map>

struct Image {
	void* data = 0;
	DWORD dataSize = 0;
	void* srv = 0;
	int width = 0, height = 0;
};

class ImageLoader : public Singleton<ImageLoader> {
public:
	bool LoadImageFromResources(int resourceNum);
	std::map<int, Image> ImagesMap;
};