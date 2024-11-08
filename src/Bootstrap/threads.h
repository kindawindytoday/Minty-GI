#pragma once
#include <Windows.h>

namespace Threads {
	DWORD MainThread(LPVOID reserved);
	DWORD BypassThread(LPVOID reserved);
}