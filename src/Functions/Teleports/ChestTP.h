#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"
#include "TeleportBase.h"
#include <map>

namespace Teleports {
	struct VectorHasher
	{
		std::size_t operator()(const Unity::Vector3& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<string>()(std::to_string(k.x))
				^ (hash<string>()(std::to_string(k.y)) << 1)) >> 1)
				^ (hash<float>()(k.z) << 1);
		}
	};

	class ChestTP : public Feature, public Singleton<ChestTP> {
	public:
		Hotkey h_TP;

		MoleMole::BaseEntity* ClosestEntity;
		int Distance;

		MoleMole::BaseEntity* cachedAvatar = 0;
		Unity::Camera* cachedCamera = 0;
		std::vector<MoleMole::BaseEntity*> cachedEntities;
		std::map<int, MoleMole::BaseEntity*> chestMap;
		size_t cachedSize = 0;
#define DIRTY_CACHE() cachedEntities.clear()

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		ChestTP();
	};
}