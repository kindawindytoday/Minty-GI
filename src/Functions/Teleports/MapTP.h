#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"
#include "TeleportBase.h"
#include <map>

namespace Teleports {
	class MapTP : public Feature, public Singleton<MapTP> {
	public:
		Hotkey h_TP;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		MapTP();
	};
}