#include "SkipCutscene.h"

namespace Visuals {
	void hook_CriwareMediaPlayer_Update(void* this_);

	void SkipCutscene::InitConfig() {}

	void SkipCutscene::InitHooks() {
		//Hooks::Attach(Offsets::CriwareMediaPlayer::Update, hook_CriwareMediaPlayer_Update);
	}

	SkipCutscene::SkipCutscene() : Feature(
		"Skip cutscenes",
		"Automatically skips cutscenes")
	{
		InitConfig();
		InitHooks();
	}

	void SkipCutscene::Options() {}

	void SkipCutscene::Status() {}

	void SkipCutscene::OnUpdate() {}

	void SkipCutscene::ProcessHotkeys() {}

	void hook_CriwareMediaPlayer_Update(void* this_) {
		auto& instance = SkipCutscene::Instance();
		//if (instance.m_Enabled) Offsets::CriwareMediaPlayer::Skip(this_);

		Hooks::Call(hook_CriwareMediaPlayer_Update, this_);
	}
}