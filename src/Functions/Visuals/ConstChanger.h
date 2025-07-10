#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class ConstChanger : public Feature, public Singleton<ConstChanger> {
	public:
		ConfigField<int> i_ConstellationLevel;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		ConstChanger();
	};
}