#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../FeatureManager.h"

namespace Player {
	class Invincibility : public Feature, public Singleton<Invincibility> {
	public:
		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();
		void DetachHooks();

		Invincibility();
	};
}