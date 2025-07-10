#include "MultiHit.h"

namespace Player {
	void Hook_MultiHit_FireBeingHitEvent(void* this_, uint32_t attackeeId, void* attackResult);

	void HitMultiplier::InitConfig() {
		i_Hits = Config::GetValue(this->m_Name, ("hits"), 2);
	}

	void HitMultiplier::InitHooks() {
		Hooks::Attach(Offsets::LCBaseCombat::FireBeingHitEvent, Hook_MultiHit_FireBeingHitEvent);
	}

	HitMultiplier::HitMultiplier() : Feature(
		("Hit Multiplier"),
		("Multiplies your attacks"))
	{
		InitConfig();
		InitHooks();
	}

	void HitMultiplier::Options()
	{
		ConfigSliderInt("Hits", i_Hits, 1, 5);
	}

	void HitMultiplier::Status() {}

	void HitMultiplier::OnUpdate() {}

	void HitMultiplier::ProcessHotkeys() {}

	void Hook_MultiHit_FireBeingHitEvent(void* this_, uint32_t attackeeId, void* attackResult) {
		auto& instance = HitMultiplier::Instance();

		if (instance.m_Enabled && attackeeId != MoleMole::EntityManager::get_EntityManager()->avatar()->runtimeId()) {
			for (int i = 0; i < instance.i_Hits; ++i) {
				Hooks::Call(Hook_MultiHit_FireBeingHitEvent, this_, attackeeId, attackResult);
			}
			return;
		}

		Hooks::Call(Hook_MultiHit_FireBeingHitEvent, this_, attackeeId, attackResult);
	}
}