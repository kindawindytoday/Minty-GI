#pragma once

#include "../Frameworks/ImGui/imgui_impl_dx11.h"
#include "../Frameworks/ImGui/imgui_impl_win32.h"
#include "../Misc/Globals.h"
#include "../Misc/ResourceLoader.h"
#include "../Misc/stb_image.h"
#include "Layout.h"
#include <d3d11.h>
#include <thread>
#include <Windows.h>

namespace GUI {
	static ID3D11Device* pd3dDevice;
	static ID3D11DeviceContext* pd3dDeviceContext;
	static IDXGISwapChain* pSwapChain;
	static ID3D11RenderTargetView* pMainRenderTargetView;
	static HMODULE currentModule;

	LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	bool CreateDevice(HWND hwnd);
	void CleanupDevice();
	void CreateRenderTarget();
	void CleanupRenderTarget();

	// Menu stuff
	void Init();
	bool Render();

	// Image loading
	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
}