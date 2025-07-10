#pragma once
#include "ESPBase.h"

namespace World {
	class ESP : public Feature, public Singleton<ESP> {
	public:

		/*ConfigField<bool> b_TpEnabled;
		ConfigField<ESPBase::TpMode> i_TpMode;
		Hotkey h_ClosestTP;
		std::map<int, RPG::GameEntity> mapActors;

		float f_ClosestActor;
		RPG::GameEntity closestActor;*/

		MoleMole::BaseEntity* cachedAvatar = 0;
		Unity::Camera* cachedCamera = 0;

		float f_BoxColor[4]     = { 100 / 255.f, 150 / 255.f, 100 / 255.f, 200 / 255.f };
		float f_OutlineColor[4] = { 200 / 255.f, 200 / 255.f, 200 / 255.f, 255 / 255.f };
		bool  b_DrawLines;

		bool b_Monsters;
		bool b_NPCs;
		bool b_Animals;
		bool b_Chests;
		bool b_Oculi;
		bool b_Collectibles;
		bool b_Puzzles;
		bool b_Challenges;
		bool b_Destroyables;
		bool b_Ores;

		float f_Range;

#define DIRTY_CACHE() cachedEntities.clear()
		std::map<float, MoleMole::BaseEntity*> cachedEntities;
		size_t cachedSize;

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		ESP();
	};
}