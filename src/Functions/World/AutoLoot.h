#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace World {
	class AutoLoot : public Feature, public Singleton<AutoLoot> {
	public:
		ConfigField<bool> b_AutoChests;

		ConfigField<float> f_LootRange;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		AutoLoot();
	};
}