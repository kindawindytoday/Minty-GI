#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace Visuals {
	class FlycloakChanger : public Feature, public Singleton<FlycloakChanger> {
	public:
		std::map<int, std::string> v_FlycloakList = {
			{140004, "Wings of Azure Wind"},
			{140002, "Wings of Companionship"},
			{140006, "Wings of Concealing Snow"},
			{140014, "Wings of Delicacies"},
			{140003, "Wings of Descension"},
			{140016, "Wings of Fate's Course Intertwined"},
			{140007, "Wings of Feasting"},
			{140001, "Wings of First Flight"},
			{140005, "Wings of Golden Flight"},
			{140012, "Wings of Merciful, Wrathful Waters"},
			{140009, "Wings of Shimmering Galaxy"},
			{140015, "Wings of Soaring Flame"},
			{140010, "Wings of the Forest"},
			{140011, "Wings of the Starlit Feast"},
			{140008, "Wings of the Stormstrider"},
			{140013, "Wings of Transient Dreams"}
		};

		ConfigField<int> i_CurrentFlycloak;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		FlycloakChanger();
	};
}