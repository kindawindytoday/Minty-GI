#include "InfinityUltimate.h"

namespace Player {
	float hook_GetEnergy(void* this_);
	bool hook_IsEnergySkillAvailable(void* this_);

	void InfinityUltimate::InitConfig() {}

	void InfinityUltimate::InitHooks() {
		Hooks::Attach(Offsets::LCAvatarCombat::get_Energy, hook_GetEnergy);
		Hooks::Attach(Offsets::LCAvatarCombat::IsEnergySkillAvailable, hook_IsEnergySkillAvailable);
	}

	InfinityUltimate::InfinityUltimate() : Feature(
		("Infinite Burst"),
		("Charges burst energy"))
	{
		InitConfig();
		InitHooks();
	}

	void InfinityUltimate::Options() {}

	void InfinityUltimate::Status() {}

	void InfinityUltimate::OnUpdate() {}

	void InfinityUltimate::ProcessHotkeys() {}

	float hook_GetEnergy(void* this_) {
		auto& instance = InfinityUltimate::Instance();
		if (instance.m_Enabled)
			return 1.0f;

		return Hooks::Call(hook_GetEnergy, this_);
	}

	bool hook_IsEnergySkillAvailable(void* this_) {
		auto& instance = InfinityUltimate::Instance();
		if (instance.m_Enabled)
			return true;

		return Hooks::Call(hook_IsEnergySkillAvailable, this_);
	}
}