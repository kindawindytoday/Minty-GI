#include "PlayerSpeed.h"

namespace Player {
	void OnUpdate_PlayerSpeed();

	void PlayerSpeed::InitConfig() {
		f_Speed = Config::GetValue(this->m_Name, ("speed"), 1.5f);
	}

	void PlayerSpeed::InitHooks() {}

	PlayerSpeed::PlayerSpeed() : Feature(
		("Player speed"),
		("Speeds up player animations"))
	{
		InitConfig();
		InitHooks();
	}

	void PlayerSpeed::Options() {
		ConfigSliderFloat(("Speed"), f_Speed, 0.1f, 2.f);
	}

	void PlayerSpeed::Status() {}

	void PlayerSpeed::OnUpdate() {}

	void PlayerSpeed::ProcessHotkeys() {}

	void OnUpdate_PlayerSpeed() {
		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		auto& instance = PlayerSpeed::Instance();

		Offsets::Animator::set_Speed(MoleMole::EntityManager::get_EntityManager()->avatar()->animator(), instance.m_Enabled ? instance.f_Speed : 1.00f);
	}
}