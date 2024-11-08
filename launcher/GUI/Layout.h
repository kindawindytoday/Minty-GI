#pragma once

#include "../Frameworks/ImGui/imgui_impl_dx11.h"
#include "../Frameworks/ImGui/imgui_impl_win32.h"
#include "../Frameworks/Json/json.hpp"
#include "../Misc/Singleton.h"
#include "FontsLoader.h"
#include "ImageLoader.h"
#include <fstream>
#include <functional>
#include <map>
#include <string>
#include <Windows.h>

enum PageIndex {
	PageLoading = 1,
	PageMain = 2
};

struct Page {
	PageIndex index;
	std::function<void()> code;
};

class MainWindow : public Singleton<MainWindow> {
public:
	// Fields
	bool Opened;
	ImVec2 WindowPos;
	ImVec2 WindowSize;
	std::map<int, std::function<void()>> PagesMap;
	PageIndex CurrentPage = PageLoading;
	int CurrentProject = 0;

	// Constants
	const ImGuiWindowFlags mainWindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse;

	// Methods
	void DrawTabBar();
	void DrawMain();
	void InitWindow();
	void AddPage(Page page);
};