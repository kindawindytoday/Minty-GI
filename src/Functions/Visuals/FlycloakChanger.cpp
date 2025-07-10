#include "FlycloakChanger.h"

namespace Visuals {
	void hook_HandleAvatarAppear2(void* this_, MoleMole::SceneEntityInfo* info, void* a1, uint32_t a2);

	void FlycloakChanger::InitConfig() {
		i_CurrentFlycloak = Config::GetValue(this->m_Name, "flycloak", 140014);
	}

	void FlycloakChanger::InitHooks() {
		Hooks::Attach(Offsets::PlayerModule::HandleAvatarAppear2, hook_HandleAvatarAppear2);
	}

	FlycloakChanger::FlycloakChanger() : Feature(
		"Change Glider",
		"Changes your Glider. Change avatar to apply.")
	{
		InitConfig();
		InitHooks();
	}

	void FlycloakChanger::Options() {
		if (ImGui::BeginCombo("Flycloak", v_FlycloakList[i_CurrentFlycloak].c_str())) {
			for (auto& [id, name] : v_FlycloakList) {
				if (ImGui::Selectable(name.c_str())) {
					i_CurrentFlycloak.setValue(id);
					Config::SetValue(i_CurrentFlycloak, id);
				}
			}
			ImGui::EndCombo();
		}
	}

	void FlycloakChanger::Status() {}

	void FlycloakChanger::OnUpdate() {}

	void FlycloakChanger::ProcessHotkeys() {}

	void hook_HandleAvatarAppear2(void* this_, MoleMole::SceneEntityInfo* info, void* a1, uint32_t a2) {
		auto& instance = FlycloakChanger::Instance();

		void* sceneAvatarInfo = *reinterpret_cast<void**>((uintptr_t)info + 0x0);
		
		if (instance.m_Enabled)
			*reinterpret_cast<uint32_t*>((uintptr_t)sceneAvatarInfo + 0x0) = instance.i_CurrentFlycloak;

		Hooks::Call(hook_HandleAvatarAppear2, this_, info, a1, a2);
	}
}