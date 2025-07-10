#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class GraphicsChanger : public Feature, public Singleton<GraphicsChanger> {
	public:
		ConfigField<bool> b_Gamma;
		ConfigField<float> f_GammaValue;

		ConfigField<bool> b_Outline;
		ConfigField<float> f_OutlineValue;

		ConfigField<bool> b_ResolutionScale;
		ConfigField<float> f_ResolutionScaleValue;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		GraphicsChanger();
	};
}