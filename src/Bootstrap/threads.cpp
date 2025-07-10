#include "threads.h"
#include "../GUI/DirectX/DirectXHook.h"
#include <iostream>

#include "../Functions/Player/NoSkillCd.h"
#include "../Functions/Player/InfinityUltimate.h"
#include "../Functions/Player/InfinityStamina.h"
#include "../Functions/Player/Noclip.h"
#include "../Functions/Player/Godmode.h"
#include "../Functions/Player/MultiHit.h"
#include "../Functions/Player/PlayerSpeed.h"
#include "../Functions/Player/WalkOnWater.h"
#include "../Functions/Player/AOEAttack.h"

//#include "../Functions/World/Speedhack.h"
#include "../Functions/World/DumbEnemies.h"
#include "../Functions/World/Autotalk.h"
//#include "../Functions/World/LootRange.h"
#include "../Functions/World/AutoLoot.h"
#include "../Functions/World/AutoDestroy.h"
#include "../Functions/World/AutoActivateTP.h"
#include "../Functions/World/AutoSeelie.h"
#include "../Functions/World/ESP.h"
#include "../Functions/World/KillAura.h"

#include "../Functions/Teleports/ChestTP.h"
#include "../Functions/Teleports/OculiTP.h"
#include "../Functions/Teleports/QuestTP.h"
#include "../Functions/Teleports/MapTP.h"

#include "../Functions/Visuals/Uncensor.h"
#include "../Functions/Visuals/SkipCutscene.h"
#include "../Functions/Visuals/FpsUnlock.h"
#include "../Functions/Visuals/FovChanger.h"
#include "../Functions/Visuals/GraphicsChanger.h"
#include "../Functions/Visuals/FlycloakChanger.h"
#include "../Functions/Visuals/ConstChanger.h"
#include "../Functions/Visuals/HideDamage.h"
#include "../Functions/Visuals/InstantBowCharge.h"
#include "../Functions/Visuals/ResinCrafter.h"
#include "../Functions/Visuals/ObjectSpawner.h"
#include "../Functions/Visuals/OpenTeamImmediately.h"
#include "../Functions/Visuals/FakeTime.h"
#include "../Functions/Visuals/FakeWeather.h"

#include "../Functions/Settings/Settings.h"

#include "../Functions/FeatureManager.h"

#include "../Utils/ResourceLoader.h"

#include "../Bypass/Bypass.h"

#include "../Utils/ProjectGlobals.h"

#define CONSOLE

DWORD Threads::MainThread(LPVOID reserved)
{
#ifdef CONSOLE
    // Init console
    AllocConsole();
    SetConsoleTitle(L" ");
    freopen(("CONIN$"), "r", stdin);
    freopen(("CONOUT$"), "w", stdout);
    freopen(("CONOUT$"), "w", stderr);

    // Prevent highlighted text stuck
    auto hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hStdin, mode);
#endif

    printf(("Started Minty-GI! ===\n"));

    ResourceLoader::Instance().SetHandle((HMODULE)reserved);

    while (!FindWindowA("UnityWndClass", nullptr))
    {
        Sleep(100);
    }
    Sleep(5000);

    printf(("Found window! Initing funcs...\n"));
    auto& instance = FeatureManager::Instance();
    instance.AddModule({ ("Player"), {
        &Player::NoSkillCd::Instance(),
        &Player::InfinityUltimate::Instance(),
        &Player::InfinityStamina::Instance(),
        &Player::Invincibility::Instance(),
        &Player::HitMultiplier::Instance(),
        //&Player::AOEAttack::Instance(),    // It was too late to release this
        &Player::Noclip::Instance(),
        &Player::PlayerSpeed::Instance(),
        &Player::WalkOnWater::Instance(),
    } });
    instance.AddModule({ ("World"), {
        &World::DumbEnemies::Instance(),
        &World::Autotalk::Instance(),
        &World::AutoLoot::Instance(),
        &World::AutoDestroy::Instance(),      // It was too late to release this
        &World::AutoSeelie::Instance(),       // It was too late to release this
        &World::AutoActivateTP::Instance(),   // It was too late to release this
        &World::KillAura::Instance(),
        //&World::ESP::Instance(),            // Removed before public release due to instability
    } });
    instance.AddModule({ "Teleports", {       // Whole section could be risky
        &Teleports::ChestTP::Instance(),
        &Teleports::OculiTP::Instance(),
        &Teleports::QuestTP::Instance(),
        &Teleports::MapTP::Instance(),
    } });
    instance.AddModule({ ("Misc"), {
        &Visuals::SkipCutscene::Instance(),
        &Visuals::FlycloakChanger::Instance(),
        &Visuals::ConstChanger::Instance(),
        &Visuals::InstantBowCharge::Instance(),
        &Visuals::ResinCrafter::Instance(),
        &Visuals::ObjectSpawner::Instance(),
        &Visuals::OpenTeamImmediately::Instance(),
        &Visuals::FakeTime::Instance(),       // It was too late to release this
        &Visuals::FakeWeather::Instance(),    // It was too late to release this
    } });
    instance.AddModule({ ("Visuals"), {
        &Visuals::Uncensor::Instance(),
        &Visuals::FpsUnlock::Instance(),
        &Visuals::FovChanger::Instance(),
        &Visuals::GraphicsChanger::Instance(),
        //&Visuals::HideDamage::Instance(),    // Stopped working in 5.7
    } });
    instance.AddModule({ ("Settings"), {
        &Settings::Configs::Instance()
    } });

    printf(("Functions inited! HOOKING DX ===\n"));
    DxHook::HookPresent();

    return 0;
}

DWORD Threads::BypassThread(LPVOID reserved)
{
    Bypass::Init();
    return 0;
}
