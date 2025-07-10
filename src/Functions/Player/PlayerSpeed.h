#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Player {
	class PlayerSpeed : public Feature, public Singleton<PlayerSpeed> {
	public:
		ConfigField<float> f_Speed;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		PlayerSpeed();
	};
}