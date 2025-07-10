#include "MapTP.h"

namespace Teleports {
	void hook_InLevelMapPageContext_OnMapClicked(void* this_, Unity::Vector2 pos);
	void hook_InLevelMapPageContext_OnMarkClicked(void* this_, void* mark);

	void MapTP::InitConfig()
	{
		h_TP = Hotkey(m_Name, ("TP"), ImGuiKey_T);
	}

	void MapTP::InitHooks()
	{
		Hooks::Attach(Offsets::InLevelMapPageContext::OnMapClicked, hook_InLevelMapPageContext_OnMapClicked);
		Hooks::Attach(Offsets::InLevelMapPageContext::OnMarkClicked, hook_InLevelMapPageContext_OnMarkClicked);
	}

	MapTP::MapTP() : Feature(
		("Map TP"),
		("Click on the map while holding TP key to teleport to that location"))
	{
		InitConfig();
		InitHooks();
	}

	void MapTP::Options()
	{
		h_TP.Draw(("TP key"));
	}

	void MapTP::Status() {}

	void MapTP::OnUpdate() {}

	void MapTP::ProcessHotkeys() {}

	void hook_InLevelMapPageContext_OnMapClicked(void* this_, Unity::Vector2 pos)
	{
		auto& instance = MapTP::Instance();

		if (instance.m_Enabled && instance.h_TP.IsDown())
		{
			auto mgr = Offsets::SingletonManager::get_Instance();
			if (mgr != nullptr)
			{
				auto uiManager = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString(("<...>")));
				if (uiManager != nullptr)
				{
					auto monoInLevelMapPage = *reinterpret_cast<void**>((uintptr_t)this_ + 0x0);
					if (monoInLevelMapPage != nullptr)
					{
						auto mapBackground = Offsets::MonoInLevelMapPage::get_mapBackground(monoInLevelMapPage);
						if (mapBackground != nullptr)
						{
							auto uiCamera = *reinterpret_cast<void**>((uintptr_t)uiManager + 0x0);
							if (uiCamera != nullptr)
							{
								Unity::Vector2 levelPos = { 0,0 };

								if (Offsets::RectTransformUtility::ScreenPointToLocalPointInRectangle(mapBackground, pos, uiCamera, &levelPos))
								{
									auto mapRect = Offsets::MonoInLevelMapPage::get_mapRect(monoInLevelMapPage);
									auto mapViewRect = *reinterpret_cast<MoleMole::Rect*>((uintptr_t)this_ + 0x0);

									levelPos.x = (levelPos.x - mapRect.m_XMin) / mapRect.m_Width;
									levelPos.x = (levelPos.x * mapViewRect.m_Width) + mapViewRect.m_XMin;
											
									levelPos.y = (levelPos.y - mapRect.m_YMin) / mapRect.m_Height;
									levelPos.y = (levelPos.y * mapViewRect.m_Height) + mapViewRect.m_YMin;

									auto worldPos = Offsets::Miscs::GenWorldPos(levelPos);
									auto relativePos = Offsets::WorldShiftManager::GetRelativePosition(worldPos);
									worldPos.y = Offsets::Miscs::CalcCurrentGroundHeight(relativePos.x, relativePos.z) + 10.f;

									std::thread(TeleportBase::TeleportTo, worldPos, 0).detach();

									Offsets::BasePageContext::ClosePage(this_);
								}
							}
						}
					}
				}
			}
		}

		Hooks::Call(hook_InLevelMapPageContext_OnMapClicked, this_, pos);
	}

	void hook_InLevelMapPageContext_OnMarkClicked(void* this_, void* mark)
	{
		auto& instance = MapTP::Instance();

		if (instance.m_Enabled && instance.h_TP.IsDown())
		{
			auto mapPos = Offsets::MonoMapMark::get_levelMapPos(mark);
			auto worldPos = Offsets::Miscs::GenWorldPos(mapPos);
			auto relativePos = Offsets::WorldShiftManager::GetRelativePosition(worldPos);
			worldPos.y = Offsets::MonoMapMark::get_height(mark) + 3.f;

			std::thread(TeleportBase::TeleportTo, worldPos, 0).detach();

			Offsets::BasePageContext::ClosePage(this_);
		}

		Hooks::Call(hook_InLevelMapPageContext_OnMarkClicked, this_, mark);
	}
}
