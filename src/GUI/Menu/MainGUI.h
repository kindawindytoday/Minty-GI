#pragma once

#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Frameworks/ImGui/ImGuiNotify.hpp"
#include "../../Utils/Singleton.h"
#include "../../Functions/FeatureManager.h"
#include "../Images/ImageLoader.h"
#include "../Fonts/FontsLoader.h"
#include <functional>
#include <thread>

class Menu : public Singleton<Menu> {
public:
	bool b_Opened = true;

	bool b_Teleporting = false;
	float f_TeleportingAlpha = 0.f;

	const void DrawFrame();
	const void DrawStatus();
	const void DrawFPS();
	void DrawTeleportingScreen();

	const void ExecuteHotkeys();
	const void ExecuteOuter();
};