#include "HideDamage.h"

namespace Visuals {
	void hook_MonoParticleDamageTextContainer_ShowDamegeText(void* this_, void* a1, void* a2);

	void HideDamage::InitConfig() {}

	void HideDamage::InitHooks() {
		Hooks::Attach(Offsets::MonoParticleDamageTextContainer::ShowDamegeText, hook_MonoParticleDamageTextContainer_ShowDamegeText);
	}

	HideDamage::HideDamage() : Feature(
		"Hide damage text",
		"Hides damage text")
	{
		InitConfig();
		InitHooks();
	}

	void HideDamage::Options() {}

	void HideDamage::Status() {}

	void HideDamage::OnUpdate() {}

	void HideDamage::ProcessHotkeys() {}

	void hook_MonoParticleDamageTextContainer_ShowDamegeText(void* this_, void* a1, void* a2) {
		auto& instance = HideDamage::Instance();
		if (instance.m_Enabled)
			return;
		Hooks::Call(hook_MonoParticleDamageTextContainer_ShowDamegeText, this_, a1, a2);
	}
}