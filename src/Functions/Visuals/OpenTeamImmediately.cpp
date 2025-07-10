#include "OpenTeamImmediately.h"

namespace Visuals {
	void InLevelPageContext_UpdateView(void* this_);

	void OpenTeamImmediately::InitConfig() {

	}

	void OpenTeamImmediately::InitHooks() 
	{
		Hooks::Attach(Offsets::InLevelPageContext::UpdateView, InLevelPageContext_UpdateView);
	}

	OpenTeamImmediately::OpenTeamImmediately() : Feature(
		"Open team immediately",
		"Allows you to open team setup immediately")
	{
		InitConfig();
		InitHooks();
	}

	void OpenTeamImmediately::Options() {}

	void OpenTeamImmediately::Status() {}

	void OpenTeamImmediately::OnUpdate() {}

	void OpenTeamImmediately::ProcessHotkeys() {}

	void InLevelPageContext_UpdateView(void* this_) 
	{
		auto& instance = OpenTeamImmediately::Instance();
		
		if (instance.m_Enabled)
		{
			*reinterpret_cast<float*>((uintptr_t)this_ + 0x0) = 2.f;
		}

		Hooks::Call(InLevelPageContext_UpdateView, this_);
	}
}