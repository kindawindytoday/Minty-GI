#include "InstantBowCharge.h"

namespace Visuals {
	bool hook_SetDynamicFloat(void* this_, Unity::String* a1, float a2, bool a3);

	void InstantBowCharge::InitConfig() {}

	void InstantBowCharge::InitHooks() {
		Hooks::Attach(Offsets::ActorAbilityPlugin::SetDynamicFloat, hook_SetDynamicFloat);
	}

	InstantBowCharge::InstantBowCharge() : Feature(
		"Instant bow charge",
		"Fully charges bow instantly")
	{
		InitConfig();
		InitHooks();
	}

	void InstantBowCharge::Options() {}

	void InstantBowCharge::Status() {}

	void InstantBowCharge::OnUpdate() {}

	void InstantBowCharge::ProcessHotkeys() {}

	bool hook_SetDynamicFloat(void* this_, Unity::String* a1, float a2, bool a3) {
		auto& instance = InstantBowCharge::Instance();

		if (instance.m_Enabled && (a1->ToCString().find("Enchanted_Time") != std::string::npos)) {
			a2 = 10.00f;
		}

		return Hooks::Call(hook_SetDynamicFloat, this_, a1, a2, a3);
	}
}