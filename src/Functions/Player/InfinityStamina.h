#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Player {
	class InfinityStamina : public Feature, public Singleton<InfinityStamina> {
	public:
		ConfigField<bool> b_NightSoul;
		ConfigField<bool> b_Wanderer;
		ConfigField<bool> b_Mavuika;
		ConfigField<bool> b_Yelan;
		ConfigField<bool> b_Sayu;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		InfinityStamina();
	};
}