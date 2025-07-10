#include "DumbEnemies.h"

namespace World {
	void hook_TryDoSkill(void* this_, uint32_t skillId);

	void DumbEnemies::InitConfig() {
	}

	void DumbEnemies::InitHooks() {
		Hooks::Attach(Offsets::VCMonsterAIController::TryDoSkill, hook_TryDoSkill);
	}

	DumbEnemies::DumbEnemies() : Feature(
		"Dumb Enemies",
		"Enemies won't attack you")
	{
		InitConfig();
		InitHooks();
	}

	void DumbEnemies::Options() {}

	void DumbEnemies::Status() {}

	void DumbEnemies::OnUpdate() {}

	void DumbEnemies::ProcessHotkeys() {}

	void hook_TryDoSkill(void* this_, uint32_t skillId) {
		auto& instance = DumbEnemies::Instance();
		if (instance.m_Enabled)
			return;

		Hooks::Call(hook_TryDoSkill, this_, skillId);
	}
}