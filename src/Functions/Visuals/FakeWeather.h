#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"
#include <map>

static std::map<std::string, std::string> weatherMap = {
	{"Clear", "Data/Environment/Weather/BigWorld/Weather_ClearSky"},
	{"Cloudy", "Data/Environment/Weather/BigWorld/Weather_Cloudy"},
	{"Foggy", "Data/Environment/Weather/BigWorld/Weather_Foggy"},
	{"Storm", "Data/Environment/Weather/BigWorld/Weather_Storm"},
	{"Rain", "Data/Environment/Weather/BigWorld/Weather_Dq_Tabeisha_Rain_Heavy"},
	{"Snow", "Data/Environment/Weather/BigWorld/Weather_Snowmountain_Snow_Light"},
	{"East Coast", "Data/Environment/Weather/BigWorld/Weather_Snowmountain_EastCoast"},
};

namespace Visuals {
	class FakeWeather : public Feature, public Singleton<FakeWeather> {
	public:
		ConfigField<std::string> s_Weather;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		FakeWeather();
	};
}