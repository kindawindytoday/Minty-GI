#include "KillAura.h"

namespace World 
{
	void hook_VCAnimatorMove_LateTick(void* this_, float tick);
	void hook_RequestSceneEntityMoveReq(void* this_, uint32_t entityId, MoleMole::MotionInfo* motionInfo, bool a1, uint32_t a2, uint32_t a3);

	extern void DrawVisualRange(float range);

	void KillAura::InitConfig() {
		f_Range = Config::GetValue(this->m_Name, "range", 5.f);
		i_Type.setValue(1);
	}

	void KillAura::InitHooks() {
		Hooks::Attach(Offsets::LevelSyncCombatPlugin::RequestSceneEntityMoveReq, hook_RequestSceneEntityMoveReq);
		Hooks::Attach(Offsets::VCAnimatorMove::LateTick, hook_VCAnimatorMove_LateTick);
	}

	KillAura::KillAura() : Feature(
		"Kill Aura",
		"Automatically kills enemies around you")
	{
		InitConfig();
		InitHooks();
	}

	void hook_VCAnimatorMove_LateTick(void* this_, float tick) {
		auto& instance = KillAura::Instance();
		if (instance.m_Enabled && instance.i_Type == 0) {
			MoleMole::BaseEntity* monster = *reinterpret_cast<MoleMole::BaseEntity**>((uintptr_t)this_ + 0x0);
			if (monster->type() == MoleMole::EntityType::Monster) {
				auto avatarPos = MoleMole::EntityManager::get_EntityManager()->avatar()->getPosition();
				float distance = monster->getPosition().distance(avatarPos);

				if (distance <= instance.f_Range) {
					*reinterpret_cast<int*>((uintptr_t)this_ + 0x0) = 2;
					Offsets::VCAnimatorMove::DrownWater(this_);
				}
			}
		}

		Hooks::Call(hook_VCAnimatorMove_LateTick, this_, tick);
	}

	void hook_RequestSceneEntityMoveReq(void* this_, uint32_t entityId, MoleMole::MotionInfo* motionInfo, bool a1, uint32_t a2, uint32_t a3)
	{
		auto& instance = KillAura::Instance();

		if (instance.m_Enabled && instance.i_Type == 1) 
		{
			auto mgr = MoleMole::EntityManager::get_EntityManager();
			auto entity = Offsets::EntityManager::GetValidEntity(mgr, entityId);

			if (entity->type() == MoleMole::EntityType::Monster)
			{
				auto avatarPos = MoleMole::EntityManager::get_EntityManager()->avatar()->getPosition();
				float distance = entity->getPosition().distance(avatarPos);
				
				if (distance <= instance.f_Range)
				{
					motionInfo->pos4->y = -52525252;
				}
			}
		}

		Hooks::Call(hook_RequestSceneEntityMoveReq, this_, entityId, motionInfo, a1, a2, a3);
	}

	void KillAura::Options() 
	{
		if (ImGui::BeginCombo("Kill aura type", KillAuraTypes[i_Type].c_str())) {
			if (ImGui::Selectable(KillAuraTypes[0].c_str())) {
				i_Type.setValue(0);
				Config::SetValue(i_Type, 0);
			}
			if (ImGui::Selectable(KillAuraTypes[1].c_str())) {
				i_Type.setValue(1);
				Config::SetValue(i_Type, 1);
			}

			ImGui::EndCombo();
		}
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("'Overworld': better in world and safer, DON'T USE IN DUNGEONS!\n'Dungeon': slower than 'Overworld', but works in dungeons.");
		}

		ConfigSliderFloat("Range", f_Range, 0, 10);
		//if (ImGui::IsItemActive())
			//DrawVisualRange(f_Range);
	}

	void KillAura::Status() {
		ImGui::Text("Kill aura");
	}

	void KillAura::OnUpdate() {}

	void KillAura::ProcessHotkeys() {}
}