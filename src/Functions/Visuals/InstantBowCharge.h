#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class InstantBowCharge : public Feature, public Singleton<InstantBowCharge> {
	public:
		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		InstantBowCharge();
	};
}