#include "InfinityStamina.h"

namespace Player {
	void hook_HandleNormalProp(void* this_, uint32_t a1, long a2, void* a3);

	void hook_Wanderer_Tick(void* this_, float a1);
	void hook_Wanderer_SetValue(void* this_, float a1);

	void InfinityStamina::InitConfig() {
		this->b_Mavuika = Config::GetValue(this->m_Name, ("mavuika"), false);
		this->b_NightSoul = Config::GetValue(this->m_Name, ("nightsoul"), false);
		this->b_Wanderer = Config::GetValue(this->m_Name, ("wanderer"), false);
	}

	void InfinityStamina::InitHooks() {
		Hooks::Attach(Offsets::WandererFlightHandler::Tick, hook_Wanderer_Tick);
		Hooks::Attach(Offsets::WandererFlightHandler::SetValue, hook_Wanderer_SetValue);
		Hooks::Attach(Offsets::DataItem::HandleNormalProp, hook_HandleNormalProp)
	}

	InfinityStamina::InfinityStamina() : Feature(
		("Infinite Stamina"),
		("Makes your stamina infinite"))
	{
		InitConfig();
		InitHooks();
	}

	void InfinityStamina::Options() {
		ConfigCheckbox(("Infinite Wanderer flight"), b_Wanderer);
	}

	void InfinityStamina::Status() {}

	void InfinityStamina::OnUpdate() {}

	void InfinityStamina::ProcessHotkeys() {}

	void hook_HandleNormalProp(void* this_, uint32_t a1, long a2, void* a3) {
		auto& instance = InfinityStamina::Instance();

		if (instance.m_Enabled &&
			a1 == 10010 ||
			a1 == 10049 ||
			a1 == 10011 ||
			a1 == 10050)
		{
			return;
		}

		Hooks::Call(hook_HandleNormalProp, this_, a1, a2, a3);
	}

	void hook_Wanderer_Tick(void* this_, float a1) {
		auto& instance = InfinityStamina::Instance();
		if (instance.m_Enabled && instance.b_Wanderer) {
			a1 = 0.000001;
		}
		Hooks::Call(hook_Wanderer_Tick, this_, a1);
	}

	void hook_Wanderer_SetValue(void* this_, float a1) {
		auto& instance = InfinityStamina::Instance();
		if (instance.m_Enabled && instance.b_Wanderer) {
			return;
		}
		Hooks::Call(hook_Wanderer_SetValue, this_, a1);
	}
}