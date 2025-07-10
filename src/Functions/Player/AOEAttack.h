#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../FeatureManager.h"

namespace Player {
	class AOEAttack : public Feature, public Singleton<AOEAttack> {
	public:
		ConfigField<float> f_Range;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();
		void DetachHooks();

		AOEAttack();
	};
}