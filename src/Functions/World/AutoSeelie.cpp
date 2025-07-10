#include "AutoSeelie.h"

namespace World {
	void hook_AutoSeelie_OnUpdate(void* this_);

	void AutoSeelie::InitConfig() {}

	void AutoSeelie::InitHooks() {
		Hooks::Attach(Offsets::GameManager::Update, hook_AutoSeelie_OnUpdate);
	}

	AutoSeelie::AutoSeelie() : Feature(
		"Auto Seelie",
		"Once you first 'activate' the seelie, it will start automatically going to the target.")
	{
		InitConfig();
		InitHooks();
	}

	void AutoSeelie::Options() 
	{
		ConfigCheckbox("Speedup Seelies", b_SpeedupSeelies);
	}

	void AutoSeelie::Status() {}

	void AutoSeelie::OnUpdate() {}

	void AutoSeelie::ProcessHotkeys() {}

	std::map<uint32_t, MoleMole::BaseEntity*> entityMap;
	void hook_AutoSeelie_OnUpdate(void* this_)
	{
		auto& instance = AutoSeelie::Instance();

		if (instance.m_Enabled)
		{
			auto entityManager = MoleMole::EntityManager::get_EntityManager();
			if (entityManager)
			{
				auto avatar = entityManager->avatar();
				if (avatar)
				{
					auto avatarPos = avatar->getPosition();

					for (auto& entity : entityManager->entities())
					{
						if (entity->type() == MoleMole::EntityType::Platform)
						{
							if (entity->name().find("Seelie") != std::string::npos)
							{
								entityMap[entity->runtimeId()] = entity;
								entity->setPosition(avatarPos);
							}
						}
					}
				}
			}
		}

		if (instance.b_SpeedupSeelies)
		{
			for (auto& [id, entity] : entityMap)
			{
				auto animator = entity->animator();
				if (animator)
					Offsets::Animator::set_Speed(animator, instance.m_Enabled ? 5.0f : 1.0f);
			}
		}

		if (!entityMap.empty())
			entityMap.clear();

		Hooks::Call(hook_AutoSeelie_OnUpdate, this_);
	}
}