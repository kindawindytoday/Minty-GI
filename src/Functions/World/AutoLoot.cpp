#define IMGUI_DEFINE_MATH_OPERATORS
#include "AutoLoot.h"
#include "ESPBase.h"

namespace World {
	void hook_AddInteeBtnById(void* this_, MoleMole::BaseEntity* entity);
	bool hook_LCSelectPickup_IsInPosition(void* this_, MoleMole::BaseEntity* intee);
	bool hook_LCSelectPickup_IsOutPosition(void* this_, MoleMole::BaseEntity* intee);

	void DrawVisualRange(float range);

	void OnUpdate_AutoLoot();

	void AutoLoot::InitConfig() {
		f_LootRange = Config::GetValue(this->m_Name, "range", 5.f);
		b_AutoChests = Config::GetValue(this->m_Name, "chests", false);
	}

	void AutoLoot::InitHooks() {
		Hooks::Attach(Offsets::LCSelectPickup::AddInteeBtnById, hook_AddInteeBtnById);
		Hooks::Attach(Offsets::LCSelectPickup::IsInPosition, hook_LCSelectPickup_IsInPosition);
		Hooks::Attach(Offsets::LCSelectPickup::IsOutPosition, hook_LCSelectPickup_IsOutPosition);
	}

	AutoLoot::AutoLoot() : Feature(
		"Auto Loot",
		"Automatically picks items up")
	{
		InitConfig();
		InitHooks();
	}

	void AutoLoot::Options() {
		ConfigCheckbox("Auto chests", b_AutoChests);
		ConfigSliderFloat("Loot range", f_LootRange, 1, 10);
		//if (ImGui::IsItemActive())
			//DrawVisualRange(f_LootRange);
	}

	void AutoLoot::Status() {}

	float DistanceV2(ImVec2 value1, ImVec2 value2)
	{
		float v1 = value1.x - value2.x;
		float v2 = value1.y - value2.y;
		return sqrt((v1 * v1) + (v2 * v2));
	}

	void AutoLoot::OnUpdate() {}

	void AutoLoot::ProcessHotkeys() {}

	void hook_AddInteeBtnById(void* this_, MoleMole::BaseEntity* entity) {
		auto& instance = AutoLoot::Instance();
		if (instance.m_Enabled)
		{
			auto mgr = Offsets::SingletonManager::get_Instance();
			if (mgr != nullptr)
			{
				auto itemModule = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString("<...>"));
				if (itemModule != nullptr) 
				{
					auto entityId = entity->runtimeId();

					if (entity->type() == MoleMole::EntityType::GatherObject ||
						entity->type() == MoleMole::EntityType::EnvAnimal ||
						entity->type() == MoleMole::EntityType::DropItem)
					{
						Offsets::ItemModule::PickItem(itemModule, entityId);
					}
				}
				return;
			}
		}

		Hooks::Call(hook_AddInteeBtnById, this_, entity);
	}

	bool hook_LCSelectPickup_IsInPosition(void* this_, MoleMole::BaseEntity* intee) {
		auto& instance = AutoLoot::Instance();
		bool ret = Hooks::Call(hook_LCSelectPickup_IsInPosition, this_, intee);

		if (instance.m_Enabled) {
			auto mgr = MoleMole::EntityManager::get_EntityManager();
			if (mgr == nullptr) return ret;

			auto avatar = mgr->avatar();
			if (avatar == nullptr) return ret;

			float distance = avatar->getPosition().distance(intee->getPosition());

			auto type = intee->type();
			if (type != MoleMole::EntityType::GatherObject &&
				type != MoleMole::EntityType::GatherPoint &&
				type != MoleMole::EntityType::HomeGatherObject &&
				type != MoleMole::EntityType::DropItem &&
				type != MoleMole::EntityType::EnvAnimal)
			{
				return ret;
			}

			if (distance <= instance.f_LootRange) return true;
		}
		return ret;
	}

	bool hook_LCSelectPickup_IsOutPosition(void* this_, MoleMole::BaseEntity* intee) {
		auto& instance = AutoLoot::Instance();
		bool ret = Hooks::Call(hook_LCSelectPickup_IsInPosition, this_, intee);

		if (instance.m_Enabled) {
			auto mgr = MoleMole::EntityManager::get_EntityManager();
			if (mgr == nullptr) return ret;

			auto avatar = mgr->avatar();
			if (avatar == nullptr) return ret;

			float distance = avatar->getPosition().distance(intee->getPosition());

			auto type = intee->type();
			if (type != MoleMole::EntityType::GatherObject &&
				type != MoleMole::EntityType::GatherPoint &&
				type != MoleMole::EntityType::HomeGatherObject &&
				type != MoleMole::EntityType::DropItem &&
				type != MoleMole::EntityType::EnvAnimal)
			{
				return ret;
			}

			if (distance <= instance.f_LootRange) return true;
		}
		return ret;
	}

	void OnUpdate_AutoLoot() {
		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		auto& instance = AutoLoot::Instance();
		if (instance.m_Enabled && instance.b_AutoChests) 
		{
			auto entMgr = MoleMole::EntityManager::get_EntityManager();
			if (entMgr == nullptr) return;

			auto ents = entMgr->entities();
			if (ents.empty()) return;

			auto avatar = entMgr->avatar();
			if (avatar == nullptr) return;

			auto mgr = Offsets::SingletonManager::get_Instance();
			if (mgr != nullptr) {
				auto itemModule = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString("<...>"));
				if (itemModule == nullptr) return;

				for (auto& ent : ents)
				{
					if (ent->type() != MoleMole::EntityType::Chest) continue;
					if (ent->getPosition().distance(avatar->getPosition()) > instance.f_LootRange) continue;

					auto entityId = ent->runtimeId();
					Offsets::ItemModule::PickItem(itemModule, entityId);
				}
			}
		}
	}

	void DrawEllipseInQuad(ImVec2 A, ImVec2 B, ImVec2 C, ImVec2 D) {
		ImVec2 center = (A + B + C + D) * 0.25f;
		float rx = (B.x - A.x) * 0.5f;
		float ry = (C.y - A.y) * 0.5f;

	    int numSegments = 8;
		std::vector<ImVec2> ellipsePoints;

		for (int i = 0; i < numSegments; i++) {
			float angle = i * (2.0f * 3.14f / numSegments);
			float x = center.x + rx * cos(angle);
			float y = center.y + ry * sin(angle);
			ellipsePoints.push_back(ImVec2(x, y));
		}

		for (int i = 0; i < ellipsePoints.size(); i++) {
			ImGui::GetBackgroundDrawList()->AddLine(ellipsePoints[i], ellipsePoints[(i + 1) % ellipsePoints.size()], IM_COL32(255, 255, 255, 255));
		}
	}

	void DrawVisualRange(float range) {
		//printf("1\n");
		auto camera = Offsets::Camera::get_main();
		if (camera == nullptr) return;
		//printf("2\n");
		auto entmgr = MoleMole::EntityManager::get_EntityManager();
		if (entmgr == nullptr) return;
		//printf("3\n");
		auto avatar = entmgr->avatar();
		if (avatar == nullptr) return;
		//printf("4\n");

		auto pos = Offsets::WorldShiftManager::GetRelativePosition(avatar->getPosition());
		if (pos.zero()) return;

		auto p2 = Offsets::Camera::WorldToScreenPoint(camera, pos);
		ImGui::GetBackgroundDrawList()->AddCircleFilled({p2.x, p2.y}, 5, 0xFF0000FF);

		ImVec2 points[256] = {};

		float angle_step = 2.0f * IM_PI / 256;

		for (int i = 0; i < 256; i++) 
		{
			float angle = i * angle_step;

			Unity::Vector3 point;
			point.x = pos.x + (range * cosf(angle));
			point.y = pos.y;
			point.z = pos.z + (range * sinf(angle));

			points[i] = ESPBase::WorldToScreen(point, camera);

			ImGui::GetBackgroundDrawList()->AddCircleFilled(points[i], 2.5, IM_COL32(226, 251, 220, 200));
		}

		auto posToDraw_A = ESPBase::WorldToScreen(Unity::Vector3(pos.x + range, pos.y, pos.z), camera); // Right
		auto posToDraw_B = ESPBase::WorldToScreen(Unity::Vector3(pos.x - range, pos.y, pos.z), camera); // Left
		auto posToDraw_C = ESPBase::WorldToScreen(Unity::Vector3(pos.x, pos.y, pos.z + range), camera); // Forward
		auto posToDraw_D = ESPBase::WorldToScreen(Unity::Vector3(pos.x, pos.y, pos.z - range), camera); // Back

		float radiusY = DistanceV2(posToDraw_A, posToDraw_B) / 2;
		float radiusX = DistanceV2(posToDraw_C, posToDraw_D) / 2;

		ImGui::GetBackgroundDrawList()->AddQuadFilled(posToDraw_C, posToDraw_A, posToDraw_D, posToDraw_B, IM_COL32(226, 251, 220, 100));
	}
}