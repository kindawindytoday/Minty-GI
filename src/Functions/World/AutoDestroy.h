#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace World {
	class AutoDestroy : public Feature, public Singleton<AutoDestroy> {
	public:
		ConfigField<bool> b_Ores;
		ConfigField<bool> b_Props;
		ConfigField<bool> b_Shields;

		ConfigField<float> f_Range;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		AutoDestroy();
	};
}