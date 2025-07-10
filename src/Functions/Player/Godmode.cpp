#include "Godmode.h"

namespace Player {
	void hook_VCHumanoidMove_NotifyLandVelocity(void* this_, Unity::Vector3 a1, float a2);
	void Hook_Godmode_FireBeingHitEvent(void* this_, uint32_t attackeeId, void* attackResult);

	void Invincibility::InitConfig() {}

	void Invincibility::InitHooks() {
		Hooks::Attach(Offsets::LCBaseCombat::FireBeingHitEvent, Hook_Godmode_FireBeingHitEvent);
		Hooks::Attach(Offsets::VCHumanoidMove::NotifyLandVelocity, hook_VCHumanoidMove_NotifyLandVelocity);
	}

	Invincibility::Invincibility() : Feature(
		("Invincibility"),
		("Makes your character invincible"))
	{
		InitConfig();
		InitHooks();
	}

	void Invincibility::Options() {}

	void Invincibility::Status() {};

	void Invincibility::OnUpdate() {};

	void Invincibility::ProcessHotkeys() {}

	void Hook_Godmode_FireBeingHitEvent(void* this_, uint32_t attackeeId, void* attackResult) {
		auto& instance = Invincibility::Instance();
		if (instance.m_Enabled && attackeeId == MoleMole::EntityManager::get_EntityManager()->avatar()->runtimeId())
			return;
		Hooks::Call(Hook_Godmode_FireBeingHitEvent, this_, attackeeId, attackResult);
	}

	void hook_VCHumanoidMove_NotifyLandVelocity(void* this_, Unity::Vector3 a1, float a2) 
	{
		auto& instance = Invincibility::Instance();
		if (instance.m_Enabled)
			return;

		Hooks::Call(hook_VCHumanoidMove_NotifyLandVelocity, this_, a1, a2);
	}
}