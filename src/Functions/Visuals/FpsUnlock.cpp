#include "FpsUnlock.h"

namespace Visuals {
	void hook_GameManager_Update(void* this_);
	void OnUpdate_FPSUnlock();

	void FpsUnlock::InitConfig() {
		i_Limit = Config::GetValue(this->m_Name, "limit", 120);
	}

	void FpsUnlock::InitHooks() {
		Hooks::Attach(Offsets::GameManager::Update, hook_GameManager_Update);
	}

	FpsUnlock::FpsUnlock() : Feature(
		"FPS unlock",
		"Unlocks max. framerate")
	{
		InitConfig();
		InitHooks();
	}

	void FpsUnlock::Options() {
		ConfigSliderInt("Target FPS", i_Limit, 10, 240);
	}

	void FpsUnlock::Status() {}

	void FpsUnlock::OnUpdate() {}

	void FpsUnlock::ProcessHotkeys() {}

	void OnUpdate_FPSUnlock() {
		auto& instance = FpsUnlock::Instance();

		//if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		if (Offsets::Application::get_targetFramerate() != instance.i_Limit || !instance.m_Enabled) {
			Offsets::Application::set_targetFramerate(instance.m_Enabled ? instance.i_Limit : 60.f);
			Offsets::QualitySettings::set_vsyncCount(instance.m_Enabled ? 0 : 1);
		}
	}
}