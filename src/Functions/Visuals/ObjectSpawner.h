#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class ObjectSpawner : public Feature, public Singleton<ObjectSpawner> {
	public:
		Hotkey h_Alchemist;
		Hotkey h_Forging;
		Hotkey h_Katheryne;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		ObjectSpawner();
	};
}