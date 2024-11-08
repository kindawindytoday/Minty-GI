#pragma once
#include "MainGUI.h"

namespace GUI {
	const void Init(HWND window, ID3D11Device* device, ID3D11DeviceContext* context);
	const void Render();
}