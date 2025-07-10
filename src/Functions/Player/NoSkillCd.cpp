#include "NoSkillCd.h"
#include <fstream>
namespace Player {
	void hook_TickSkillCd(void* this_, float a1);
	void hook_UpdateSprintCooldown(void* this_, float tick);

	void NoSkillCd::InitConfig() {
		b_NoSprintCd = Config::GetValue(this->m_Name, ("noSprintCd"), false);
	}

	void NoSkillCd::InitHooks() {
		Hooks::Attach(Offsets::LCAvatarCombat::TickSkillCd, hook_TickSkillCd);
		Hooks::Attach(Offsets::HumanoidMoveFSM::UpdateSprintCooldown, hook_UpdateSprintCooldown);
	}

	NoSkillCd::NoSkillCd() : Feature(
		("No skill cooldown"),
		("Removes skill cooldown"))
	{
		InitConfig();
		InitHooks();
	}

	void NoSkillCd::Options() {
		ConfigCheckbox(("No sprint CD"), b_NoSprintCd);
	}

	void NoSkillCd::Status() {}

	void NoSkillCd::OnUpdate() {}

	void NoSkillCd::ProcessHotkeys() {}

	void hook_TickSkillCd(void* this_, float a1) {
		auto& instance = NoSkillCd::Instance();
		if (instance.m_Enabled)
			a1 = 0.9f;
		Hooks::Call(hook_TickSkillCd, this_, a1);
	}

	void hook_UpdateSprintCooldown(void* this_, float tick) {
		auto& instance = NoSkillCd::Instance();
		if (instance.m_Enabled)
			tick = 0.5f;
		Hooks::Call(hook_UpdateSprintCooldown, this_, tick);
	}
}