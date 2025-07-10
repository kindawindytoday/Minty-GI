#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

namespace World {
	class KillAura : public Feature, public Singleton<KillAura> {
	public:
		ConfigField<float> f_Range;
		ConfigField<int> i_Type;

		bool kill = false;

		std::string KillAuraTypes[2] = {"Overworld", "Dungeon"};

		void Options();
		void Status();
		void OnUpdate();
		void ProcessHotkeys();

		void InitConfig();
		void InitHooks();

		KillAura();
	};
}

/*
a1: 880804931
a2: 41005001
a7: 0
a8: 16777250
a9: 33554902
a10: 0
a11: 0
a13: 1
a14: 0
a16: 0
a17: 0
a18: 16777250
a19: 0
a21: 1
a22: 0
a23: 0
a26: 0
a27: 0
a28: 0
a30: 0
a31: 0
a32: 0
a34: 1041
a35: 0
*/

/*
a1: 880804905
a2: 41005001
a7: 0
a8: 16777250
a9: 33554902
a10: 0
a11: 0
a13: 1
a14: 0
a16: 0
a17: 0
a18: 16777250
a19: 0
a21: 1
a22: 0
a23: 0
a26: 0
a27: 0
a28: 0
a30: 0
a31: 0
a32: 0
a34: 1041
a35: 0
*/

/*
	Called gadget with configId: 41005001!
	Called gadget at 1805.470459, 207.455673, -1248.931519!
	a1: 880804921
	a2: 41005001
	a7: 0
	a8: 16777250
	a9: 33554900
	a10: 0
	a11: 0
	a13: 1
	a14: 0
	a16: 0
	a17: 0
	a18: 16777250
	a19: 0
	a21: 1
	a22: 0
	a23: 0
	a26: 0
	a27: 0
	a28: 0
	a30: 0
	a31: 0
	a32: 0
	a34: 1041
	a35: 0
	
	Called gadget with configId: 42101006!
	Called gadget at 1809.213257, 208.641098, -1283.700684!
	a1: 880804922
	a2: 42101006
	a7: 0
	a8: 33554901
	a9: 16777250
	a10: 0
	a11: 0
	a13: 1
	a14: 0
	a16: 0
	a17: 0
	a18: 33554901
	a19: 0
	a21: 1
	a22: 0
	a23: 0
	a26: 0
	a27: 0
	a28: 0
	a30: 0
	a31: 0
	a32: 0
	a34: 529
	a35: 0
	
	Called gadget with configId: 42101006!
	Called gadget at 1809.333130, 208.731140, -1283.842651!
	a1: 880804923
	a2: 42101006
	a7: 0
	a8: 33554901
	a9: 16777250
	a10: 0
	a11: 0
	a13: 1
	a14: 0
	a16: 0
	a17: 0
	a18: 33554901
	a19: 0
	a21: 1
	a22: 0
	a23: 0
	a26: 0
	a27: 0
	a28: 0
	a30: 0
	a31: 0
	a32: 0
	a34: 529
	a35: 0
	
	Called gadget with configId: 42101006!
	Called gadget at 1809.447754, 208.798416, -1284.011475!
	a1: 880804924
	a2: 42101006
	a7: 0
	a8: 33554901
	a9: 16777250
	a10: 0
	a11: 0
	a13: 1
	a14: 0
	a16: 0
	a17: 0
	a18: 33554901
	a19: 0
	a21: 1
	a22: 0
	a23: 0
	a26: 0
	a27: 0
	a28: 0
	a30: 0
	a31: 0
	a32: 0
	a34: 529
	a35: 0
	
	Called gadget with configId: 42101006!
	Called gadget at 1809.181763, 208.728088, -1283.788940!
	a1: 880804927
	a2: 42101006
	a7: 0
	a8: 33554901
	a9: 16777250
	a10: 0
	a11: 0
	a13: 1
	a14: 0
	a16: 0
	a17: 0
	a18: 33554901
	a19: 0
	a21: 1
	a22: 0
	a23: 0
	a26: 0
	a27: 0
	a28: 0
	a30: 0
	a31: 0
	a32: 0
	a34: 529
	a35: 0
	*/