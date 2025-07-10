#include "OculiTP.h"
#include "ChestTP.h"

namespace Teleports {
	void OnUpdate_OculiTP();

	void OculiTP::InitConfig()
	{
		h_TP = Hotkey(m_Name, ("TP"), ImGuiKey_P);
	}

	void OculiTP::InitHooks() {
		Distance = 0;
		ClosestEntity = nullptr;
	}

	OculiTP::OculiTP() : Feature(
		("Oculi TP"),
		("Teleports you to closest oculus"))
	{
		InitConfig();
		InitHooks();
	}

	void OculiTP::Options()
	{
		h_TP.Draw(("TP key"));
	}

	void OculiTP::Status() {}

	void OculiTP::OnUpdate()
	{
		if (!m_Enabled)
			return;

		ImGui::SetNextWindowPos({ 300, 100 }, ImGuiCond_FirstUseEver);
		ImGui::Begin(("##TP"), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
		if (!ChestTP::Instance().m_Enabled)
		{
			ImGui::Text(("  TP Status:"));
			ImGui::Separator();
		}
		ImGui::Text(("Oculi TP: %s"), ClosestEntity == nullptr ? "Not found" : std::string(std::to_string(Distance) + "m").c_str());
		ImGui::End();
	}

	void OculiTP::ProcessHotkeys()
	{
		if (m_Enabled && h_TP.IsPressed())
		{
			if (ClosestEntity == nullptr)
				return;

			auto pos = ClosestEntity->getPosition();
			if (pos.zero())
				return;

			std::thread(TeleportBase::TeleportTo, pos, 0).detach();
		}
	}

	void OnUpdate_OculiTP() {
		auto& instance = OculiTP::Instance();

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
			//printf(QENC("[OculiTP] cache is wrong! recaching...\n").c_str());

			instance.cachedSize = entities.size();
			instance.cachedEntities.clear();

			for (auto entity : entities)
			{
				if (entity == nullptr) continue;
				auto entityName = entity->name();
				if (entityName.find(("WindCrystalShell")) != std::string::npos ||
					entityName.find(("Prop_ElectricCrystal")) != std::string::npos ||
					entityName.find(("_XuMiCrystal")) != std::string::npos ||
					entityName.find(("RockCrystalShell")) != std::string::npos ||
					entityName.find(("_FontaineCrystal")) != std::string::npos ||
					entityName.find(("_NataCrystal")) != std::string::npos)
				{
					instance.cachedEntities.push_back(entity);
				}
			}

			if (instance.cachedEntities.empty())
			{
				instance.Distance = 0;
				instance.ClosestEntity = nullptr;
			}

			//printf(QENC("[OculiTP] recaching done!\n").c_str());
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