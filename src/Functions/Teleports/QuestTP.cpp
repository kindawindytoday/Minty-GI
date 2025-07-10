#include "QuestTP.h"

namespace Teleports {
	void hook_MonoMapMark_Update(void* this_);

	void QuestTP::InitConfig()
	{
		targetMark = nullptr;

		h_TP = Hotkey(m_Name, ("TP"), ImGuiKey_I);
	}

	void QuestTP::InitHooks()
	{
		Hooks::Attach(Offsets::MonoMapMark::Update, hook_MonoMapMark_Update);
	}

	QuestTP::QuestTP() : Feature(
		("Quest TP"),
		("Teleports you to active tracked quest"))
	{
		InitConfig();
		InitHooks();
	}

	void QuestTP::Options()
	{
		h_TP.Draw(("TP key"));
	}

	void QuestTP::Status() {}

	void QuestTP::OnUpdate() {}

	void QuestTP::ProcessHotkeys()
	{
		if (m_Enabled && h_TP.IsPressed())
		{
			if (targetMark == nullptr)
				return;

			Unity::Vector3 targetPos = {};

			auto mapPos = Offsets::MonoMapMark::get_levelMapPos(targetMark);
			auto worldPos = Offsets::Miscs::GenWorldPos(mapPos);
			worldPos.y = Offsets::MonoMapMark::get_height(targetMark) + 3.f;

			targetPos = worldPos;

			targetPos.x += 1;
			targetPos.z += 1;

			std::thread(TeleportBase::TeleportTo, targetPos, 0).detach();
		}
	}

	void hook_MonoMapMark_Update(void* this_)
	{
		auto& instance = QuestTP::Instance();

		if (instance.m_Enabled)
		{
			void* transform = Offsets::Component::get_transform(this_);
			if (transform != nullptr)
			{
				void* parent = Offsets::Transform::get_parent(transform);
				if (parent != nullptr)
				{
					void* gameObject = Offsets::Component::get_gameObject(parent);
					if (gameObject != nullptr)
					{
						auto name = Offsets::Object::get_name(gameObject);
						if (name != nullptr)
						{
							if (name->ToCString().find(("Layer3")) != std::string::npos)
							{
								void* generalMarkData = *reinterpret_cast<void**>((uintptr_t)this_ + 0x0);
								if (generalMarkData != nullptr)
								{
									int markType = *reinterpret_cast<int*>((uintptr_t)generalMarkData + 0x0);
									if (markType == 2 || markType == 10)
									{
										instance.targetMark = this_;
									}
								}
							}
						}
					}
				}
			}
		}

		Hooks::Call(hook_MonoMapMark_Update, this_);
	}
}
