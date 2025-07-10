#include "AutoActivateTP.h"

namespace World {
	void hook_LCScenePoint_Tick(void* this_, float tick);

	void AutoActivateTP::InitConfig() {}

	void AutoActivateTP::InitHooks() 
	{
		Hooks::Attach(Offsets::LCScenePoint::Tick, hook_LCScenePoint_Tick);
	}

	AutoActivateTP::AutoActivateTP() : Feature(
		"Auto Activate TP",
		"Automatically unlocks TP points near you")
	{
		InitConfig();
		InitHooks();
	}

	void AutoActivateTP::Options() {}

	void AutoActivateTP::Status() {}

	void AutoActivateTP::OnUpdate() {}

	void AutoActivateTP::ProcessHotkeys() {}

	void hook_LCScenePoint_Tick(void* this_, float tick)
	{
		// ¯\_(ツ)_/¯	
	}
}