#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"
#include <thread>

class ESPBase {
public:
	// Structs
	enum class DrawMode {
		Box = 1,
		Chams = 2
	};

	enum class PointMode {
		Line = 1,
		Arrows = 2,
		None = 3
	};

	enum class TpMode : int {
		Closest = 0,
		OnClick = 1
	};
	static inline const char* TpModeNames[2] = { "Closest", "On Click" };

	struct Bounds {
		Unity::Vector3 center;
		Unity::Vector3 extent;

		Unity::Vector3 p_min();
		Unity::Vector3 p_max();
	};

	// Utils
	static inline ImVec4 ColorVecToImVec(std::vector<float> color);
	static inline Bounds GetBoundsFromActor(MoleMole::BaseEntity* actor);
	static ImVec2 WorldToScreen(Unity::Vector3 world, Unity::Camera* camera);

	// Drawing
	static void DrawActor(MoleMole::BaseEntity* actor, MoleMole::BaseEntity* avatar, Unity::Camera* camera, ESPBase::DrawMode drawmode, ESPBase::PointMode pointmode, std::vector<float> borderColor, std::vector<float> boxColor, std::function<void(MoleMole::BaseEntity*)> onClickCallback = 0); // RGBA
};