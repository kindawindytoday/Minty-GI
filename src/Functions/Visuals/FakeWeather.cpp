#include "FakeWeather.h"

namespace Visuals {
	void hook_FakeWeather_OnUpdate(void* this_);

	void FakeWeather::InitConfig()
	{
		s_Weather = Config::GetValue<std::string>(this->m_Name, "weather", "Clear");
	}

	void FakeWeather::InitHooks() {
		Hooks::Attach(Offsets::GameManager::Update, hook_FakeWeather_OnUpdate);
	}

	FakeWeather::FakeWeather() : Feature(
		"Fake Weather",
		"Changes weather in the world")
	{
		InitConfig();
		InitHooks();
	}

	void FakeWeather::Options()
	{
		if (ImGui::BeginCombo("Weather type", s_Weather.getValue().c_str()))
		{
			for (auto& [name, path] : weatherMap)
			{
				if (ImGui::Selectable(name.c_str()))
				{
					s_Weather.setValue(name);
					Config::SetValue(s_Weather, name);
				}
			}
			ImGui::EndCombo();
		}
	}

	void FakeWeather::Status() {}

	void FakeWeather::OnUpdate() {}

	void FakeWeather::ProcessHotkeys() {}

	void hook_FakeWeather_OnUpdate(void* this_)
	{
		auto& instance = FakeWeather::Instance();

		if (instance.m_Enabled)
		{
			auto enviroSky = Offsets::EnviroSky::get_Instance();
			if (enviroSky)
			{
				auto path = weatherMap[instance.s_Weather.getValue()];
				Offsets::EnviroSky::ChangeWeather(enviroSky, Unity::String::FromCString(path), 1, 1, false);
			}
		}

		Hooks::Call(hook_FakeWeather_OnUpdate, this_);
	}
}