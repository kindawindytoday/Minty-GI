#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"
#include "TeleportBase.h"
#include <map>

namespace Teleports {
	class QuestTP : public Feature, public Singleton<QuestTP> {
	public:
		Hotkey h_TP;

		void* targetMark;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		QuestTP();
	};
}