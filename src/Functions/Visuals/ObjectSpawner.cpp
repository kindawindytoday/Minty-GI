#include "ObjectSpawner.h"

namespace Visuals {
	void Spawn_Alchem();
	void Spawn_Forging();
	void Spawn_Katheryne();

	void ObjectSpawner::InitConfig() {
		h_Alchemist = Hotkey(this->m_Name, "alchemist", ImGuiKey_F9);
		h_Forging = Hotkey(this->m_Name, "forging", ImGuiKey_F10);
		h_Katheryne = Hotkey(this->m_Name, "katheryne", ImGuiKey_F11);
	}

	void ObjectSpawner::InitHooks() {}

	ObjectSpawner::ObjectSpawner() : Feature(
		"Object spawner",
		"Spawns some useful objects")
	{
		InitConfig();
		InitHooks();
	}

	void ObjectSpawner::Options() {
		if (ImGui::Button("Alchemists' Bench")) {
			Spawn_Alchem();
		} ImGui::SameLine(); h_Alchemist.Draw();

		if (ImGui::Button("Forging Bench")) {
			Spawn_Forging();
		} ImGui::SameLine(); h_Forging.Draw();

		if (ImGui::Button("Katheryne")) {
			Spawn_Katheryne();
		} ImGui::SameLine(); h_Katheryne.Draw();
	}

	void ObjectSpawner::Status() {}

	void ObjectSpawner::OnUpdate() {}

	void ObjectSpawner::ProcessHotkeys() {
		if (m_Enabled && h_Alchemist.IsPressed()) Spawn_Alchem();
		if (m_Enabled && h_Forging.IsPressed()) Spawn_Forging();
		if (m_Enabled && h_Katheryne.IsPressed()) Spawn_Katheryne();
	}

	void Spawn_Alchem() {
		// ¯\_(ツ)_/¯
	}

	void Spawn_Forging() {
		// ¯\_(ツ)_/¯
	}

	void Spawn_Katheryne() {
		// ¯\_(ツ)_/¯
	}
}