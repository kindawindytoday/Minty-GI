#include "ConstChanger.h" 

namespace Visuals {
	void hook_ConstChanger_HandleAvatarAppear2(void* this_, MoleMole::SceneEntityInfo* info, void* a1, uint32_t a2);

	void ConstChanger::InitConfig() {
		i_ConstellationLevel = Config::GetValue(this->m_Name, "level", 6);
	}

	void ConstChanger::InitHooks() {
		Hooks::Attach(Offsets::PlayerModule::HandleAvatarAppear2, hook_ConstChanger_HandleAvatarAppear2);
	}

	ConstChanger::ConstChanger() : Feature(
		"C6 Unlocker",
		"Unlocks C6 on your character. Switch avatar to apply.\nMost constellations will not have actual effect, though some still will. Do not report it as a bug.\nDISABLE BEFORE GOING INTO ABYSS!")
	{
		InitConfig();
		InitHooks();
	}

	void ConstChanger::Options() {}

	void ConstChanger::Status() {}

	void ConstChanger::OnUpdate() {}

	void ConstChanger::ProcessHotkeys() {}

	void hook_ConstChanger_HandleAvatarAppear2(void* this_, MoleMole::SceneEntityInfo* info, void* a1, uint32_t a2) {
		auto& instance = ConstChanger::Instance();

		if (instance.m_Enabled)
		{
			void* sceneAvatarInfo = *reinterpret_cast<void**>((uintptr_t)info + 0x0);
			if (sceneAvatarInfo != nullptr)
			{
				MoleMole::RepeatedField* talentIdList = *reinterpret_cast<MoleMole::RepeatedField**>((uintptr_t)sceneAvatarInfo + 0x0);
				if (talentIdList != nullptr)
				{
					int avatarId = *reinterpret_cast<uint32_t*>((uintptr_t)sceneAvatarInfo + 0x0) - 10'000'000;
					talentIdList->count = 6;
					talentIdList->array->max_length = 6;
					for (int i = 1; i <= instance.i_ConstellationLevel; i++)
					{
						talentIdList->array->vector[i] = (avatarId * 10) + i;
					}
				}
			}
		}

		Hooks::Call(hook_ConstChanger_HandleAvatarAppear2, this_, info, a1, a2);
	}
}