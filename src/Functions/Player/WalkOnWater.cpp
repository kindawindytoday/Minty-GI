#include "WalkOnWater.h"

namespace Player {
	bool hook_VCBaseMove_CanWalkOnWater(void* this_);

	void WalkOnWater::InitConfig() {}

	void WalkOnWater::InitHooks() {
		Hooks::Attach(Offsets::VCBaseMove::CanWalkOnWater, hook_VCBaseMove_CanWalkOnWater);
	}

	WalkOnWater::WalkOnWater() : Feature(
		("Walk on water"),
		("Lets you walk on the water"))
	{
		InitConfig();
		InitHooks();
	}

	void WalkOnWater::Options() {}

	void WalkOnWater::Status() {}

	void WalkOnWater::OnUpdate() {}

	void WalkOnWater::ProcessHotkeys() {}

	bool hook_VCBaseMove_CanWalkOnWater(void* this_) {
		auto& instance = WalkOnWater::Instance();
		if (instance.m_Enabled)
			return true;

		return Hooks::Call(hook_VCBaseMove_CanWalkOnWater, this_);
	}
}	