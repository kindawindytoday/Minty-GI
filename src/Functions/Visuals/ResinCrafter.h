#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class ResinCrafter : public Feature, public Singleton<ResinCrafter> {
	public:
		ConfigField<int> i_ResinPieces;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		ResinCrafter();
	};
}