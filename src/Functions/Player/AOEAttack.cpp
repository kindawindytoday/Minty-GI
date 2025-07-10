#include "AOEAttack.h"

namespace Player
{
	void hook_AOE_FireBeingHit(void* this_, uint32_t attackeeId, void* res);

	void AOEAttack::InitConfig()
	{
		f_Range = Config::GetValue(this->m_Name, "range", 10.f);
	}

	void AOEAttack::InitHooks()
	{
		Hooks::Attach(Offsets::LCBaseCombat::FireBeingHitEvent, hook_AOE_FireBeingHit);
	}

	AOEAttack::AOEAttack() : Feature(
		("AOE Attack"),
		("Duplicates your attacks to all enemies in range"))
	{
		InitConfig();
		InitHooks();
	}

	void AOEAttack::Options()
	{
		ConfigSliderFloat(QENC("Attack range").c_str(), f_Range, 1.f, 100.f);
	}

	void AOEAttack::OnUpdate() {}

	void AOEAttack::Status() {}

	void AOEAttack::ProcessHotkeys() {}

	std::vector<uint32_t> GetListOfEnemies()
	{
		auto& instance = AOEAttack::Instance();
		std::vector<uint32_t> result;

		auto entityManager = MoleMole::EntityManager::get_EntityManager();
		if (entityManager == nullptr)
			return result;

		auto entityList = entityManager->entities();
		if (entityList.empty())
			return result;

		auto avatar = entityManager->avatar();
		if (avatar == nullptr)
			return result;

		auto avatarPosition = avatar->getPosition();
		if (avatarPosition.zero())
			return result;

		for (auto& entity : entityList)
		{
			if (entity->type() != MoleMole::EntityType::Monster) continue;

			float distance = avatarPosition.distance(entity->getPosition());
			if (distance <= instance.f_Range)
			{
				result.push_back(entity->runtimeId());
			}
		}

		return result;
	}

	void hook_AOE_FireBeingHit(void* this_, uint32_t attackeeId, void* res)
	{
		auto& instance = AOEAttack::Instance();

		if (instance.m_Enabled && attackeeId != MoleMole::EntityManager::get_EntityManager()->avatar()->runtimeId())
		{
			auto list = GetListOfEnemies();
			if (!list.empty())
			{
				for (uint32_t id : list)
				{
					Hooks::Call(hook_AOE_FireBeingHit, this_, id, res);
				}
			}
		}
		else
		{
			Hooks::Call(hook_AOE_FireBeingHit, this_, attackeeId, res);
		}
	}
}