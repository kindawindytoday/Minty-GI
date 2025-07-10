#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../FeatureManager.h"

namespace Settings {
	class Configs : public Feature, public Singleton<Configs> {
	public:
		ConfigField<bool> b_ShowFps;
		ConfigField<bool> b_ShowStatus;
		ConfigField<bool> b_TpScreen;
		Hotkey h_OpenMenu;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		Configs();
	};
}