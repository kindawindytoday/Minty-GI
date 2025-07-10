#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class FakeTime : public Feature, public Singleton<FakeTime> {
	public:
		ConfigField<int> i_Hours;
		ConfigField<int> i_Minutes;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		FakeTime();
	};
}