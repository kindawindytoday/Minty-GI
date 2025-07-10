#include "DirectXHook.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../Utils/stb_image.h"
#include "../../Utils/ProjectGlobals.h"
#include <psapi.h>

LRESULT CALLBACK hook_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto& instance = Menu::Instance();

	ImGui::GetIO().MouseDrawCursor = instance.b_Opened;
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

	if (uMsg == WM_PAINT) {
		HDC         hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return S_OK;
	}

	if (instance.b_Opened) {
		return true;
	}
	return CallWindowProc(OriginalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext) {
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

ResizeBuffers o_bufs;
static IDXGISwapChain* gswc = 0;
HRESULT hook_ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	//printf("resized@\n");
	if (!MainRenderTargetView)
		return o_bufs(pSwapChain, BufferCount, Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, SwapChainFlags);

	DXGI_SWAP_CHAIN_DESC Desc;
	pSwapChain->GetDesc(&Desc);

	//printf("obufs: %p\n", o_bufs);
	if (MainRenderTargetView && pContext) {
		pContext->OMSetRenderTargets(0, 0, 0);
		MainRenderTargetView->Release();
	}
	HRESULT hr = o_bufs(pSwapChain, BufferCount, Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, SwapChainFlags);
	//printf("hr: %X, %lu, %lu, %lu, %i, %lu\n", hr, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
	if (pBuffer == nullptr) return hr;

	pDevice->CreateRenderTargetView(pBuffer, NULL, &MainRenderTargetView);
	pBuffer->Release();
	pContext->OMSetRenderTargets(1, &MainRenderTargetView, NULL);

	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1, &vp);

	return hr;
}

IDXGISwapChainPresent present;

static BOOL g_bInitialised = false;
static bool g_SwapChainOccluded = false;
static DWORD_PTR* g_origResize = 0;
HRESULT __fastcall hook_Present(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags) {
	if (!g_bInitialised) {
		if (SUCCEEDED(pChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			ImGui::CreateContext();

			DXGI_SWAP_CHAIN_DESC desc0 = {};
			pChain->GetDesc(&desc0);
			window = desc0.OutputWindow;

			if (!pDevice) return present(pChain, SyncInterval, Flags);
			pDevice->GetImmediateContext(&pContext);

			ID3D11Texture2D* BackBuffer;
			pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			if (!BackBuffer) return present(pChain, SyncInterval, Flags);

			D3D11_RENDER_TARGET_VIEW_DESC desc = {};
			memset(&desc, 0, sizeof(desc));
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // most important change!
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			pDevice->CreateRenderTargetView(BackBuffer, &desc, &MainRenderTargetView);
			BackBuffer->Release();

			DWORD old = 0;
			VirtualProtect((LPVOID)g_origResize, 100, PAGE_READWRITE, &old);
			*g_origResize = (uintptr_t)hook_ResizeBuffers;
			VirtualProtect((LPVOID)g_origResize, 100, old, &old);

			GUI::Init(window, pDevice, pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (__int3264)hook_WndProc);
			g_bInitialised = true;
		}
	}

	if (!g_SwapChainOccluded && MainRenderTargetView)
	{
		GUI::Render();
		pContext->OMSetRenderTargets(1, &MainRenderTargetView, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT hr = present(pChain, SyncInterval, Flags);
	g_SwapChainOccluded = hr == DXGI_STATUS_OCCLUDED;

	return hr;
}

namespace DxHook {
	void HookPresent() {
		printf(("[...] Hooking Present...\n"));
		std::thread(findDirect11Present).detach();
		printf(("[+] Hooked present at %p\n"), present);
	}

	typedef long(*PresentImplCore)(IDXGISwapChain* this_, void* a2, uint32_t a3, void* a4, uint32_t a5, void* a6, void* a7, void* a8);
	PresentImplCore o_PresentImplCore;

	long hk_PresentImplCore(IDXGISwapChain* this_, void* a2, uint32_t a3, void* a4, uint32_t a5, void* a6, void* a7, void* a8) 
	{
		if (!gswc && this_) {
			gswc = this_;
		}

		return o_PresentImplCore(this_, a2, a3, a4, a5, a6, a7, a8);
	}

	static uintptr_t foundPIC = 0;

	uintptr_t pattern_scan(uintptr_t module_base, const char* signature) {
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);
			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module_base;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((uint8_t*)module_base + dosHeader->e_lfanew);

		auto size_of_image = ntHeaders->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte(signature);
		auto module_bytes = reinterpret_cast<uint8_t*>(module_base);

		auto s = pattern_bytes.size();
		auto d = pattern_bytes.data();
		auto CurrentSig = 0;
		int TimesFound = 0;
		for (auto i = 0ul; i < size_of_image - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (module_bytes[i + j] != d[j] && d[j] != -1) {
					found = false; // if not found keep scanning
					break;
				}
			}
			if (found) {
				return (uintptr_t)&module_bytes[i];
			}
		}
		return 0;
	}

	static IDXGISwapChainPresent findDirect11Present()
	{
		while (!GetModuleHandleA(("dxgi.dll")))
		{
			Sleep(100);
		}

		printf(("Trying pattern #1...\n"));
		foundPIC = pattern_scan((uintptr_t)GetModuleHandleA(("dxgi.dll")), ("<...>"));
		if (foundPIC == 0)
		{
			printf(("Trying pattern #2...\n"));
			foundPIC = pattern_scan((uintptr_t)GetModuleHandleA(("dxgi.dll")), ("<...>"));
			if (foundPIC == 0)
			{
				MessageBoxA(FindWindowA("UnityWndClass", 0), ("Couldn't find PIC!\nCreate a ticket in our discord server"), ("DXGI ERROR"), (MB_TOPMOST));
			}
		}

		o_PresentImplCore = (long(*)(IDXGISwapChain * this_, void* a2, uint32_t a3, void* a4, uint32_t a5, void* a6, void* a7, void* a8))(foundPIC);

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(LPVOID&)o_PresentImplCore, (hk_PresentImplCore));
		DetourTransactionCommit();

		while (!gswc) {
			Sleep(100);
		}

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(LPVOID&)o_PresentImplCore, hk_PresentImplCore);
		DetourTransactionCommit();

		const DWORD_PTR* pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(gswc);
		pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChainVtable[0]);
		
		IDXGISwapChainPresent orig = (IDXGISwapChainPresent)pSwapChainVtable[8];
		ResizeBuffers orig_resize = (ResizeBuffers)pSwapChainVtable[13];

		present = orig;
		o_bufs = orig_resize;

		auto targ = (DWORD_PTR*)(pSwapChainVtable + 8);
		auto targ_resize = (DWORD_PTR*)(pSwapChainVtable + 13);

		DWORD old = 0;
		VirtualProtect((LPVOID)targ, 100, PAGE_READWRITE, &old);
		*targ = (uintptr_t)hook_Present;
		VirtualProtect((LPVOID)targ, 100, old, &old);
		g_origResize = targ_resize;
		gswc->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
		gswc->Release();

		return orig;
	}

	bool LoadTextureFromMemory(const void* data, size_t data_size, void** out_srv, int* out_width, int* out_height)
	{
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		ID3D11SamplerState* pSamplerState = nullptr;
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.MaxAnisotropy = 16;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.MipLODBias = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.BorderColor[0] = 0;
		samplerDesc.BorderColor[1] = 0;
		samplerDesc.BorderColor[2] = 0;
		samplerDesc.BorderColor[3] = 0;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		pDevice->CreateSamplerState(&samplerDesc, &pSamplerState);
		pContext->PSSetSamplers(0, 1, &pSamplerState);

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = image_width;
		desc.Height = image_height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = image_data;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		pDevice->CreateShaderResourceView(pTexture, &srvDesc, (ID3D11ShaderResourceView**)out_srv);
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}
}