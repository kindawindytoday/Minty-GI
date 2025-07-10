#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Player {
	class NoSkillCd : public Feature, public Singleton<NoSkillCd> {
	public:
		ConfigField<bool> b_NoSprintCd;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		NoSkillCd();
	};
}