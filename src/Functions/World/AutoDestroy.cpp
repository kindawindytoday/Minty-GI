#include "AutoDestroy.h"

namespace World {
	void hook_LCAbilityModifier_ReduceModifierDurability(void* this_, int index, float reduce, void* nullable);

	void AutoDestroy::InitConfig() 
	{
		b_Ores = Config::GetValue(this->m_Name, "ores", false);
		b_Props = Config::GetValue(this->m_Name, "props", false);
		b_Shields = Config::GetValue(this->m_Name, "shields", false);
		f_Range = Config::GetValue(this->m_Name, "range", 15.f);
	}

	void AutoDestroy::InitHooks() {
		Hooks::Attach(Offsets::LCAbilityComponent::ReduceModifierDurability, hook_LCAbilityModifier_ReduceModifierDurability);
	}

	AutoDestroy::AutoDestroy() : Feature(
		"Auto Destroy",
		"Automatically destroys selected types of objects")
	{
		InitConfig();
		InitHooks();
	}

	void AutoDestroy::Options()
	{
		ConfigCheckbox("Ores", b_Ores);
		ConfigCheckbox("Scene props (barrels, boxes, ...)", b_Props);
		ConfigCheckbox("Shields", b_Shields);
		ConfigSliderFloat("Range", f_Range, 1, 50);
	}

	void AutoDestroy::Status() {}

	void AutoDestroy::OnUpdate() {}

	void AutoDestroy::ProcessHotkeys() {}

	bool IsValidEntity(MoleMole::BaseEntity* entity)
	{
		auto& instance = AutoDestroy::Instance();

		auto type = entity->type();
		auto name = entity->name();

		if (instance.b_Ores &&
			type == MoleMole::EntityType::GatherObject &&

			(name.find("_ElementRock") != std::string::npos ||
				name.find("Ore") != std::string::npos ||
				name.find("_Drop") != std::string::npos))
		{
			return true;
		}

		if (instance.b_Props &&
			type == MoleMole::EntityType::Gadget &&

			(name.find("Monster_Effigy") != std::string::npos ||
				name.find("HiliWoodenBox") != std::string::npos ||
				name.find("HumanBox") != std::string::npos ||
				name.find("HumanJars") != std::string::npos ||
				name.find("QQTotem") != std::string::npos ||
				name.find("WatchTower") != std::string::npos ||
				name.find("StonePile") != std::string::npos ||
				name.find("BrokenWall") != std::string::npos ||
				name.find("WoodenBox") != std::string::npos ||
				name.find("RoadBlock") != std::string::npos))
		{
			return true;
		}

		if (instance.b_Shields &&
			(type == MoleMole::EntityType::Monster ||
			 type == MoleMole::EntityType::MonsterEquip) &&

			(name.find("_Abyss") != std::string::npos ||
				name.find("_Slime") != std::string::npos ||
				name.find("_Brute") != std::string::npos ||
				name.find("_Invoker") != std::string::npos ||
				name.find("_Fatuus_Summoner") != std::string::npos ||
				name.find("_Skirmisher") != std::string::npos ||
				name.find("_Cicin") != std::string::npos ||
				name.find("_Mimik") != std::string::npos))
		{
			return true;
		}

		return false;
	}

	void hook_LCAbilityModifier_ReduceModifierDurability(void* this_, int index, float reduce, void* nullable)
	{
		auto& instance = AutoDestroy::Instance();

		if (instance.m_Enabled)
		{
			auto entity = *reinterpret_cast<MoleMole::BaseEntity**>((uintptr_t)this_ + 0x0);
			if (entity)
			{
				auto entityManager = MoleMole::EntityManager::get_EntityManager();
				if (entityManager)
				{
					auto avatar = entityManager->avatar();
					if (avatar)
					{
						auto avatarPos = avatar->getPosition();
						float distance = entity->getPosition().distance(avatarPos);

						if (IsValidEntity(entity) && distance <= instance.f_Range)
							reduce = 10000.f;
					}
				}
			}
		}

		Hooks::Call(hook_LCAbilityModifier_ReduceModifierDurability, this_, index, reduce, nullable);
	}
}