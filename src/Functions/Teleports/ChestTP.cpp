#include "ChestTP.h"

namespace Teleports {
	void OnUpdate_ChestTP();

	void ChestTP::InitConfig() 
	{
		h_TP = Hotkey(m_Name, ("TP"), ImGuiKey_Y);
	}

	void ChestTP::InitHooks() {
		Distance = 0;
		ClosestEntity = nullptr;
	}

	ChestTP::ChestTP() : Feature(
		("Chest TP"),
		("Teleports you to closest closed chest"))
	{
		InitConfig();
		InitHooks();
	}

	void ChestTP::Options() 
	{
		h_TP.Draw(("TP key"));
	}

	void ChestTP::Status() {}

	void ChestTP::OnUpdate()
	{
		if (!m_Enabled)
			return;

		ImGui::SetNextWindowPos({ 300, 100 }, ImGuiCond_FirstUseEver);
		ImGui::Begin(("##TP"), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		ImGui::Text(("  TP Status:"));
		ImGui::Separator();
		ImGui::Text(("Chest TP: %s"), ClosestEntity == nullptr ? "Not found" : std::string(std::to_string(Distance) + "m").c_str());
		ImGui::End();
	}

	void ChestTP::ProcessHotkeys() 
	{
		if (m_Enabled && h_TP.IsPressed())
		{
			if (ClosestEntity == nullptr)
				return;

			auto pos = ClosestEntity->getPosition();
			if (pos.zero()) 
				return;

			pos.x += 1;
			pos.z += 1;

			std::thread(TeleportBase::TeleportTo, pos, 0).detach();
		}
	}

	void OnUpdate_ChestTP() {
		auto& instance = ChestTP::Instance();

		if (!instance.m_Enabled)
			return;

		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;
		
		auto manager = MoleMole::EntityManager::get_EntityManager();
		if (manager == nullptr) return;

		auto avatar = manager->avatar();
		if (avatar == nullptr) return;

		auto avatarPos = avatar->getPosition();

		auto entities = manager->entities();

		if (instance.cachedSize != entities.size()) 
		{
			//printf(("[ChestTP] cache is wrong! recaching...\n"));

			instance.cachedSize = entities.size();
			instance.cachedEntities.clear();

			for (auto entity : entities)
			{
				if (entity == nullptr) continue;
				if (entity->name().find(("TreasureBox")) == std::string::npos) continue;
				
				instance.cachedEntities.push_back(entity);
			}

			if (instance.cachedEntities.empty())
			{
				instance.Distance = 0;
				instance.ClosestEntity = nullptr;
			}

			//printf(("[ChestTP] recaching done!\n"));
		}

		for (auto& entity : instance.cachedEntities)
		{	
			float distance = avatarPos.distance(entity->getPosition());
			instance.chestMap[distance] = entity;
		}

		if (!instance.chestMap.empty())
		{
			instance.Distance = instance.chestMap.begin()->first;
			instance.ClosestEntity = instance.chestMap.begin()->second;
		}

		instance.chestMap.clear();
	}
}