#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Player {
	class Noclip : public Feature, public Singleton<Noclip> {
	public:
		ConfigField<float> f_Speed;

		ConfigField<bool> b_UseAltSpeed;
		ConfigField<float> f_AltSpeed;

		void* cachedMgr = 0;
		void* cachedAvatar = 0;
		void* cachedCamera = 0;
		void* cachedRelativeTransform = 0;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		Noclip();
	};
}