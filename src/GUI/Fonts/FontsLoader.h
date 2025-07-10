#pragma once

#include "../../Utils/ResourceLoader.h"
#include "../../Utils/Singleton.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include <map>
#include <iostream>

namespace {
	namespace Fonts {
		namespace Kodchasan {
			namespace Regular {
				constexpr int a16 = 16;
				constexpr int a20 = 20;
				constexpr int a24 = 24;
			}
			namespace Bold {
				constexpr int a16 = 116;
				constexpr int a20 = 120;
				constexpr int a24 = 124;
			}
		}
	}
}

class FontsLoader : public Singleton<FontsLoader> {
public:
	bool LoadFont(int resourceNum, float fontSize, ImFontConfig* fontConfig, int fontId, const ImWchar* fontRanges);
	std::map<int, ImFont*> FontsMap;
};