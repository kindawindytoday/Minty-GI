#pragma once

#include "../Misc/Singleton.h"
#include "../Misc/ResourceLoader.h"
#include "InitGUI.h"
#include <Windows.h>
#include <d3d11.h>
#include <map>

namespace {
	namespace Fonts {
		namespace Jost {
			namespace Regular {
				int TitleBar = 12;
				int Header = 20;
				int MainText = 14;
			}
			namespace Light {
				int TitleBar = 121;
				int Header = 201;
				int MainText = 141;
			}
		}
	}
}

class FontsLoader : public Singleton<FontsLoader> {
public:
	std::map<int, ImFont*> FontsMap;
	void AddFont(int resourceNum, float fontSize, ImFontConfig* fontCfg, int fontId);
};