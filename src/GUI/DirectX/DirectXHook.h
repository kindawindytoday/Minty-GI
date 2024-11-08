#pragma once

#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Utils/detours.h"
#include "../../Utils/Hooking.h"
#include "../../Utils/Singleton.h"
#include "../Menu/InitGui.h"
#include "../Menu/MainGUI.h"
#include <D3D11.h>
#include <Windows.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "detours.lib")

namespace {
	typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	typedef HRESULT(__fastcall* IDXGISwapChainPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) { return DefWindowProc(hwnd, uMsg, wParam, lParam); }

	static WNDPROC OriginalWndProcHandler         = nullptr;
	ID3D11RenderTargetView* MainRenderTargetView  = nullptr;
	ID3D11DeviceContext* pContext                 = nullptr;
	ID3D11Device* pDevice                         = nullptr;
	static IDXGISwapChain* pSwapChain             = nullptr;
	ResizeBuffers oResizeBuffers                  = nullptr;
	HWND window                                   = nullptr;
	IDXGISwapChainPresent fnIDXGISwapChainPresent = nullptr;
}

namespace DxHook {
	IDXGISwapChainPresent findDirect11Present();
	void HookPresent();
	void HookResizeBuffers();
	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
}