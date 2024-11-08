#include "threads.h"
#include "../GUI/DirectX/DirectXHook.h"
#include <iostream>

DWORD Threads::MainThread(LPVOID reserved)
{
    // Init console
    AllocConsole();
    SetConsoleTitle(L"Minty-GI");
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    // Prevent highlighted text stuck
    auto hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    SetConsoleMode(hStdin, mode);

    // Init DX11 hook
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x1)) {} // Wait for ESC press
    DxHook::HookPresent();
    DxHook::HookResizeBuffers();

	return 0;
}

DWORD Threads::BypassThread(LPVOID reserved)
{
	return 0;
}
