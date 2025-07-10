#pragma once

#include "../../Engine/SDK.h"
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Feature.h"

class TeleportBase
{
public:
	static void TeleportTo(Unity::Vector3 pos, uint32_t sceneId = 0);
};