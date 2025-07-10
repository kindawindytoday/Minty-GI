#include "Autotalk.h"

namespace World {
	void hook_MonoInLevelCutScenePageContext_UpdateView(void* this_);
	void hook_MonoTypeWriter_Update(void* this_);

	void Autotalk::InitConfig() {
		b_AutoChoose = true;
	}

	void Autotalk::InitHooks() {
		Hooks::Attach(Offsets::InLevelCutScenePageContext::UpdateView, hook_MonoInLevelCutScenePageContext_UpdateView);
		Hooks::Attach(Offsets::MonoTypeWriter::Update, hook_MonoTypeWriter_Update);
	}

	Autotalk::Autotalk() : Feature(
		"Auto Dialogue",
		"Automatically goes through dialogues.")
	{
		InitConfig();
		InitHooks();
	}

	void Autotalk::Options() {
		ImGui::Checkbox("Automatically choose reply", &b_AutoChoose);
	}

	void Autotalk::Status() {}

	void Autotalk::OnUpdate() {}

	void Autotalk::ProcessHotkeys() {}

	void hook_MonoInLevelCutScenePageContext_UpdateView(void* this_)
	{
		auto& instance = Autotalk::Instance();

		void* talkDialogContext = *reinterpret_cast<void**>((uintptr_t)this_ + 0x0);
		if (talkDialogContext != nullptr)
		{
			float* protectTime = reinterpret_cast<float*>((uintptr_t)talkDialogContext + 0x0);
			if (Autotalk::Instance().m_Enabled)
				*protectTime = 0.0f;
			else
				*protectTime = 0.4f;

			void* onFreeClick = *reinterpret_cast<void**>((uintptr_t)talkDialogContext + 0x0);
			if (onFreeClick != nullptr && instance.m_Enabled)
			{
				Offsets::Action::Invoke(onFreeClick);
			}

			if (instance.b_AutoChoose && instance.m_Enabled)
			{
				void* monoTalkDialog = *reinterpret_cast<void**>((uintptr_t)talkDialogContext + 0x0);
				if (monoTalkDialog != nullptr)
				{
					void* monoselectgrp = *reinterpret_cast<void**>((uintptr_t)monoTalkDialog + 0x0);
					if (monoselectgrp != nullptr)
					{
						void* monoReusableList = *reinterpret_cast<void**>((uintptr_t)monoselectgrp + 0x0);
						if (monoReusableList != nullptr)
						{
							void* item = Offsets::MonoReusableList::get_item(monoReusableList, 0);
							if (item != nullptr)
							{
								Offsets::MonoSelectItem::OnSelectItem(item);
							}
						}
					}
				}
			}
		}

		return Hooks::Call(hook_MonoInLevelCutScenePageContext_UpdateView, this_);
	}

	void hook_MonoTypeWriter_Update(void* this_) 
	{
		auto& instance = Autotalk::Instance();
		float* _secondPerChar = reinterpret_cast<float*>((uintptr_t)this_ + 0x0);
		
		if (instance.m_Enabled)
		{
			*_secondPerChar = 0.000001f;
		}
		else
		{
			*_secondPerChar = 0.03f;
		}

		return Hooks::Call(hook_MonoTypeWriter_Update, this_);
	}
}