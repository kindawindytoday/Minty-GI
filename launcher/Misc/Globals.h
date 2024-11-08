#pragma once
#include "Singleton.h"
#include <Windows.h>

class Globals : public Singleton<Globals> {
public:
	HWND g_Hwnd = 0;
};