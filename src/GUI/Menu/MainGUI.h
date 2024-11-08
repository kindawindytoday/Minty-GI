#pragma once

#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Frameworks/ImGui/ImGuiNotify.hpp"
#include "../../Utils/Singleton.h"
#include <functional>
#include <thread>

class Menu : public Singleton<Menu> {
public:
	bool b_Opened = true;

	const void DrawFrame();
	const void DrawStatus();
	const void DrawFPS();

	const void ExecuteOverlay();
	const void ExecuteHotkeys();

	const void StartOuter();
};