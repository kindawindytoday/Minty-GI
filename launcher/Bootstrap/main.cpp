#include "../GUI/InitGUI.h"
#include "../Misc/Globals.h"
#include <fstream>
#include <thread>

#define _CRT_SECURE_NO_WARNINGS

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    /*AllocConsole();
    SetConsoleTitle(L"M-Loader");
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);*/

    GUI::Init();
    return 0;
}