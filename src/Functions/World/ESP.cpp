#include "ESP.h"

namespace World {
	void OnUpdate_ESP_Cache();
	void ESP_OnClickCallback(MoleMole::BaseEntity* entity);
	bool ESP_FilterEntity(MoleMole::BaseEntity* entity);

	void ESP::InitConfig() {
		b_DrawLines = true;

		b_Monsters = false;
		b_NPCs = false;
		b_Animals = false;
		b_Chests = false;
		b_Oculi = false;
		b_Collectibles = false;
		b_Puzzles = false;
		b_Challenges = false;
		b_Destroyables = false;
		b_Ores = false;

		f_Range = 100.f;
	}

	void ESP::InitHooks() {}

	ESP::ESP() : Feature(
		"ESP",
		"Lets you see certain objects through the walls")
	{
		InitConfig();
		InitHooks();
	}

	void ESP::Options() {
		ImGui::SeparatorText("Filters");
		if (ImGui::Checkbox("Monsters", &b_Monsters))         DIRTY_CACHE();
		if (ImGui::Checkbox("NPCs", &b_NPCs))                 DIRTY_CACHE();
		if (ImGui::Checkbox("Animals", &b_Animals))           DIRTY_CACHE();
		if (ImGui::Checkbox("Chests", &b_Chests))             DIRTY_CACHE();
		if (ImGui::Checkbox("Oculi", &b_Oculi))				  DIRTY_CACHE();
		if (ImGui::Checkbox("Collectibles", &b_Collectibles)) DIRTY_CACHE();

		ImGui::SeparatorText("Drawing");
		if (ImGui::ColorEdit4("Box color", f_BoxColor, ImGuiColorEditFlags_AlphaBar));
		if (ImGui::ColorEdit4("Outline color", f_OutlineColor, ImGuiColorEditFlags_AlphaBar));
		if (ImGui::Checkbox("Draw lines", &b_DrawLines));
		if (ImGui::SliderFloat("Draw range", &f_Range, 10, 1000)) DIRTY_CACHE();
	}

	void ESP::Status() {}

	void ESP::OnUpdate() 
	{
		if (!m_Enabled) return;

		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		if (cachedAvatar == nullptr) return;

		if (cachedCamera == nullptr) return;

		if (this->cachedEntities.empty()) return;

		for (auto entry : this->cachedEntities) 
		{
			try {
				ESPBase::DrawActor(
					entry.second,
					cachedAvatar,
					cachedCamera,
					ESPBase::DrawMode::Box, b_DrawLines ? ESPBase::PointMode::Line : ESPBase::PointMode::None,
					{ 255.f * f_OutlineColor[0], 255.f * f_OutlineColor[1], 255.f * f_OutlineColor[2], 255.f * f_OutlineColor[3] },
					{ 255.f * f_BoxColor[0],     255.f * f_BoxColor[1],     255.f * f_BoxColor[2],     255.f * f_BoxColor[3] },
					nullptr);
			}
			catch (...)
			{
				continue;
			}
		}
	}

	void ESP::ProcessHotkeys() {}

	void OnUpdate_ESP_Cache() {
		auto& instance = ESP::Instance();
		if (!instance.m_Enabled) return;

		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		auto mgr = MoleMole::EntityManager::get_EntityManager();
		if (mgr == nullptr) return;

		auto avatar = mgr->avatar();
		if (avatar == nullptr) return;

		auto playerPos = avatar->getPosition();
		if (playerPos.zero() == true) return;

		auto ents = mgr->entities();

		instance.cachedAvatar = avatar;
		instance.cachedCamera = Offsets::Camera::get_main();

		if ((instance.cachedEntities.empty() || instance.cachedSize != ents.size())) {
			//printf("cache is wrong! recaching...\n");

			instance.cachedSize = ents.size();
			instance.cachedEntities.clear();

			for (auto& entity : ents) 
			{
				if (entity == nullptr) continue;
				if (!ESP_FilterEntity(entity)) continue;

				float distance = playerPos.distance(entity->getPosition());
				if (distance > instance.f_Range) continue;

				instance.cachedEntities[distance] = entity;
			}

			//printf("recaching done!\n");
		}
	}

#define FILTER(var, cond) ((instance.##var) && (cond))
	bool ESP_FilterEntity(MoleMole::BaseEntity* entity) {
		auto& instance = ESP::Instance();
		return (
			FILTER(b_Animals, entity->type() == MoleMole::EntityType::EnvAnimal) ||
			FILTER(b_Monsters, entity->type() == MoleMole::EntityType::Monster) ||
			FILTER(b_NPCs, entity->type() == MoleMole::EntityType::NPC) ||
			FILTER(b_Chests, entity->name().find("TreasureBox") != std::string::npos) ||
			FILTER(b_Oculi, entity->type() == MoleMole::EntityType::EnergyBall) ||
			FILTER(b_Collectibles, entity->type() == MoleMole::EntityType::GatherObject)
			//FILTER(b_Puzzles,       entity->type() == MoleMole::EntityType::TODO)		  ||
			//FILTER(b_Challenges,    entity->type() == MoleMole::EntityType::TODO)		  ||
			//FILTER(b_Destroyables,  entity->type() == MoleMole::EntityType::)		  ||
			//FILTER(b_Ores,          entity->type() == MoleMole::EntityType::Ore)
			);
	}
#undef FILTER

	void ESP_OnClickCallback(MoleMole::BaseEntity* entity) {
		return;

		if (entity == nullptr) return;
		if (entity->getPosition().zero()) return;
		
		// Teleport here
		// ¯\_(ツ)_/¯
	}
}