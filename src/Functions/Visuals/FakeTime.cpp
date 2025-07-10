#include "FakeTime.h"

namespace Visuals {
	void hook_FakeTime_OnUpdate(void* this_);
	
	void FakeTime::InitConfig() 
	{
		i_Hours = Config::GetValue(this->m_Name, "hours", 12);
		i_Minutes = Config::GetValue(this->m_Name, "minutes", 00);
	}

	void FakeTime::InitHooks() {
		Hooks::Attach(Offsets::GameManager::Update, hook_FakeTime_OnUpdate);
	}

	FakeTime::FakeTime() : Feature(
		"Fake Time",
		"Changes time of the day")
	{
		InitConfig();
		InitHooks();
	}

	void FakeTime::Options() 
	{
		ConfigSliderInt("Hours", i_Hours, 0, 24);
		ConfigSliderInt("Minutes", i_Minutes, 0, 60);

		if (ImGui::Button("Set to system time"))
		{
			SYSTEMTIME st;
			GetLocalTime(&st);

			i_Hours.setValue(st.wHour);
			Config::SetValue(i_Hours, i_Hours.getValue());

			i_Minutes.setValue(st.wMinute);
			Config::SetValue(i_Minutes, i_Minutes.getValue());
		}

		ImGui::SeparatorText("Presets");

		if (ImGui::Button("Morning (06:00)"))
		{
			i_Hours.setValue(6);
			Config::SetValue(i_Hours, i_Hours.getValue());

			i_Minutes.setValue(0);
			Config::SetValue(i_Minutes, i_Minutes.getValue());
		} ImGui::SameLine();

		if (ImGui::Button("Noon (12:00)"))
		{
			i_Hours.setValue(12);
			Config::SetValue(i_Hours, i_Hours.getValue());

			i_Minutes.setValue(0);
			Config::SetValue(i_Minutes, i_Minutes.getValue());
		} ImGui::SameLine();

		if (ImGui::Button("Evening (18:00)"))
		{
			i_Hours.setValue(18);
			Config::SetValue(i_Hours, i_Hours.getValue());

			i_Minutes.setValue(0);
			Config::SetValue(i_Minutes, i_Minutes.getValue());
		} ImGui::SameLine();

		if (ImGui::Button("Midnight (24:00)"))
		{
			i_Hours.setValue(24);
			Config::SetValue(i_Hours, i_Hours.getValue());

			i_Minutes.setValue(0);
			Config::SetValue(i_Minutes, i_Minutes.getValue());
		}
	}

	void FakeTime::Status() {}

	void FakeTime::OnUpdate() {}

	void FakeTime::ProcessHotkeys() {}

	void hook_FakeTime_OnUpdate(void* this_)
	{
		auto& instance = FakeTime::Instance();

		if (instance.m_Enabled)
		{
			auto mgr = Offsets::SingletonManager::get_Instance();
			if (mgr)
			{
				auto timeManager = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString("<...>"));
				if (timeManager)
				{
					float convertedTime = (float)instance.i_Hours + ((float)instance.i_Minutes / 60.f);
					Offsets::LevelTimeManager::SetInternalTimeOfDay(timeManager, convertedTime, false, true, false);
				}
			}
		}

		Hooks::Call(hook_FakeTime_OnUpdate, this_);
	}
}