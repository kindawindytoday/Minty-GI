#include "DirectXHook.h"

// Define some internal ImGui functions, so we can use them here.
namespace {
	bool IsVkDown(int vk)
	{
		return (::GetKeyState(vk) & 0x8000) != 0;
	}

	static ImGuiKey ImGui_ImplWin32_VirtualKeyToImGuiKey(WPARAM wParam)
	{
		switch (wParam)
		{
		case VK_TAB: return ImGuiKey_Tab;
		case VK_LEFT: return ImGuiKey_LeftArrow;
		case VK_RIGHT: return ImGuiKey_RightArrow;
		case VK_UP: return ImGuiKey_UpArrow;
		case VK_DOWN: return ImGuiKey_DownArrow;
		case VK_PRIOR: return ImGuiKey_PageUp;
		case VK_NEXT: return ImGuiKey_PageDown;
		case VK_HOME: return ImGuiKey_Home;
		case VK_END: return ImGuiKey_End;
		case VK_INSERT: return ImGuiKey_Insert;
		case VK_DELETE: return ImGuiKey_Delete;
		case VK_BACK: return ImGuiKey_Backspace;
		case VK_SPACE: return ImGuiKey_Space;
		case VK_RETURN: return ImGuiKey_Enter;
		case VK_ESCAPE: return ImGuiKey_Escape;
		case VK_OEM_7: return ImGuiKey_Apostrophe;
		case VK_OEM_COMMA: return ImGuiKey_Comma;
		case VK_OEM_MINUS: return ImGuiKey_Minus;
		case VK_OEM_PERIOD: return ImGuiKey_Period;
		case VK_OEM_2: return ImGuiKey_Slash;
		case VK_OEM_1: return ImGuiKey_Semicolon;
		case VK_OEM_PLUS: return ImGuiKey_Equal;
		case VK_OEM_4: return ImGuiKey_LeftBracket;
		case VK_OEM_5: return ImGuiKey_Backslash;
		case VK_OEM_6: return ImGuiKey_RightBracket;
		case VK_OEM_3: return ImGuiKey_GraveAccent;
		case VK_CAPITAL: return ImGuiKey_CapsLock;
		case VK_SCROLL: return ImGuiKey_ScrollLock;
		case VK_NUMLOCK: return ImGuiKey_NumLock;
		case VK_SNAPSHOT: return ImGuiKey_PrintScreen;
		case VK_PAUSE: return ImGuiKey_Pause;
		case VK_NUMPAD0: return ImGuiKey_Keypad0;
		case VK_NUMPAD1: return ImGuiKey_Keypad1;
		case VK_NUMPAD2: return ImGuiKey_Keypad2;
		case VK_NUMPAD3: return ImGuiKey_Keypad3;
		case VK_NUMPAD4: return ImGuiKey_Keypad4;
		case VK_NUMPAD5: return ImGuiKey_Keypad5;
		case VK_NUMPAD6: return ImGuiKey_Keypad6;
		case VK_NUMPAD7: return ImGuiKey_Keypad7;
		case VK_NUMPAD8: return ImGuiKey_Keypad8;
		case VK_NUMPAD9: return ImGuiKey_Keypad9;
		case VK_DECIMAL: return ImGuiKey_KeypadDecimal;
		case VK_DIVIDE: return ImGuiKey_KeypadDivide;
		case VK_MULTIPLY: return ImGuiKey_KeypadMultiply;
		case VK_SUBTRACT: return ImGuiKey_KeypadSubtract;
		case VK_ADD: return ImGuiKey_KeypadAdd;
		case (VK_RETURN + 256): return ImGuiKey_KeypadEnter;
		case VK_LSHIFT: return ImGuiKey_LeftShift;
		case VK_LCONTROL: return ImGuiKey_LeftCtrl;
		case VK_LMENU: return ImGuiKey_LeftAlt;
		case VK_LWIN: return ImGuiKey_LeftSuper;
		case VK_RSHIFT: return ImGuiKey_RightShift;
		case VK_RCONTROL: return ImGuiKey_RightCtrl;
		case VK_RMENU: return ImGuiKey_RightAlt;
		case VK_RWIN: return ImGuiKey_RightSuper;
		case VK_APPS: return ImGuiKey_Menu;
		case '0': return ImGuiKey_0;
		case '1': return ImGuiKey_1;
		case '2': return ImGuiKey_2;
		case '3': return ImGuiKey_3;
		case '4': return ImGuiKey_4;
		case '5': return ImGuiKey_5;
		case '6': return ImGuiKey_6;
		case '7': return ImGuiKey_7;
		case '8': return ImGuiKey_8;
		case '9': return ImGuiKey_9;
		case 'A': return ImGuiKey_A;
		case 'B': return ImGuiKey_B;
		case 'C': return ImGuiKey_C;
		case 'D': return ImGuiKey_D;
		case 'E': return ImGuiKey_E;
		case 'F': return ImGuiKey_F;
		case 'G': return ImGuiKey_G;
		case 'H': return ImGuiKey_H;
		case 'I': return ImGuiKey_I;
		case 'J': return ImGuiKey_J;
		case 'K': return ImGuiKey_K;
		case 'L': return ImGuiKey_L;
		case 'M': return ImGuiKey_M;
		case 'N': return ImGuiKey_N;
		case 'O': return ImGuiKey_O;
		case 'P': return ImGuiKey_P;
		case 'Q': return ImGuiKey_Q;
		case 'R': return ImGuiKey_R;
		case 'S': return ImGuiKey_S;
		case 'T': return ImGuiKey_T;
		case 'U': return ImGuiKey_U;
		case 'V': return ImGuiKey_V;
		case 'W': return ImGuiKey_W;
		case 'X': return ImGuiKey_X;
		case 'Y': return ImGuiKey_Y;
		case 'Z': return ImGuiKey_Z;
		case VK_F1: return ImGuiKey_F1;
		case VK_F2: return ImGuiKey_F2;
		case VK_F3: return ImGuiKey_F3;
		case VK_F4: return ImGuiKey_F4;
		case VK_F5: return ImGuiKey_F5;
		case VK_F6: return ImGuiKey_F6;
		case VK_F7: return ImGuiKey_F7;
		case VK_F8: return ImGuiKey_F8;
		case VK_F9: return ImGuiKey_F9;
		case VK_F10: return ImGuiKey_F10;
		case VK_F11: return ImGuiKey_F11;
		case VK_F12: return ImGuiKey_F12;
		case VK_F13: return ImGuiKey_F13;
		case VK_F14: return ImGuiKey_F14;
		case VK_F15: return ImGuiKey_F15;
		case VK_F16: return ImGuiKey_F16;
		case VK_F17: return ImGuiKey_F17;
		case VK_F18: return ImGuiKey_F18;
		case VK_F19: return ImGuiKey_F19;
		case VK_F20: return ImGuiKey_F20;
		case VK_F21: return ImGuiKey_F21;
		case VK_F22: return ImGuiKey_F22;
		case VK_F23: return ImGuiKey_F23;
		case VK_F24: return ImGuiKey_F24;
		case VK_BROWSER_BACK: return ImGuiKey_AppBack;
		case VK_BROWSER_FORWARD: return ImGuiKey_AppForward;
		default: return ImGuiKey_None;
		}
	}

	void ImGui_ImplWin32_AddKeyEvent(ImGuiKey key, bool down, int native_keycode, int native_scancode = -1)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(key, down);
		io.SetKeyEventNativeData(key, native_keycode, native_scancode); // To support legacy indexing (<1.87 user code)
		IM_UNUSED(native_scancode);
	}
}

void ProcessKeys(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
		const bool is_key_down = (uMsg == WM_KEYDOWN || uMsg == WM_SYSKEYDOWN);
		if (wParam < 256)
		{
			// Submit modifiers
			ImGuiIO& io = ImGui::GetIO();
			io.AddKeyEvent(ImGuiMod_Ctrl, IsVkDown(VK_CONTROL));
			io.AddKeyEvent(ImGuiMod_Shift, IsVkDown(VK_SHIFT));
			io.AddKeyEvent(ImGuiMod_Alt, IsVkDown(VK_MENU));
			io.AddKeyEvent(ImGuiMod_Super, IsVkDown(VK_APPS));

			// Obtain virtual key code
			// (keypad enter doesn't have its own... VK_RETURN with KF_EXTENDED flag means keypad enter, see IM_VK_KEYPAD_ENTER definition for details, it is mapped to ImGuiKey_KeyPadEnter.)
			int vk = (int)wParam;
			if ((wParam == VK_RETURN) && (HIWORD(lParam) & KF_EXTENDED))
				vk = (VK_RETURN + 256);

			// Submit key event
			const ImGuiKey key = ImGui_ImplWin32_VirtualKeyToImGuiKey(vk);
			const int scancode = (int)LOBYTE(HIWORD(lParam));
			if (key != ImGuiKey_None)
				ImGui_ImplWin32_AddKeyEvent(key, is_key_down, vk, scancode);

			// Submit individual left/right modifier events
			if (vk == VK_SHIFT)
			{
				// Important: Shift keys tend to get stuck when pressed together, missing key-up events are corrected in ImGui_ImplWin32_ProcessKeyEventsWorkarounds()
				if (IsVkDown(VK_LSHIFT) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_LeftShift, is_key_down, VK_LSHIFT, scancode); }
				if (IsVkDown(VK_RSHIFT) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_RightShift, is_key_down, VK_RSHIFT, scancode); }
			}
			else if (vk == VK_CONTROL)
			{
				if (IsVkDown(VK_LCONTROL) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_LeftCtrl, is_key_down, VK_LCONTROL, scancode); }
				if (IsVkDown(VK_RCONTROL) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_RightCtrl, is_key_down, VK_RCONTROL, scancode); }
			}
			else if (vk == VK_MENU)
			{
				if (IsVkDown(VK_LMENU) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_LeftAlt, is_key_down, VK_LMENU, scancode); }
				if (IsVkDown(VK_RMENU) == is_key_down) { ImGui_ImplWin32_AddKeyEvent(ImGuiKey_RightAlt, is_key_down, VK_RMENU, scancode); }
			}
		}
	}
	}
}

LRESULT CALLBACK hook_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	auto& instance = Menu::Instance();

	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	ImGui::GetIO().MouseDrawCursor = instance.b_Opened;

	if (instance.b_Opened) {
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
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

HRESULT hook_ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
	if (MainRenderTargetView) {
		pContext->OMSetRenderTargets(0, 0, 0);
		MainRenderTargetView->Release();
	}
	HRESULT hr = oResizeBuffers(pSwapChain, 1, Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, SwapChainFlags);
	ID3D11Texture2D* pBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer);
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
HRESULT __fastcall hook_Present(IDXGISwapChain* pChain, UINT SyncInterval, UINT Flags) {
	if (!g_bInitialised) {
		if (SUCCEEDED(pChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice))) {
			ImGui::CreateContext();

			pDevice->GetImmediateContext(&pContext);

			DXGI_SWAP_CHAIN_DESC Desc;
			pChain->GetDesc(&Desc);
			window = Desc.OutputWindow;

			ID3D11Texture2D* BackBuffer;
			pChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
			pDevice->CreateRenderTargetView(BackBuffer, NULL, &MainRenderTargetView);
			BackBuffer->Release();

			GUI::Init(window, pDevice, pContext);
			ImGui_ImplDX11_CreateDeviceObjects();

			OriginalWndProcHandler = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (__int3264)(LONG_PTR)hook_WndProc);
			g_bInitialised = true;
		}
	}

	GUI::Render();

	pContext->OMSetRenderTargets(1, &MainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return present(pChain, SyncInterval, Flags);
}

namespace DxHook {
	ResizeBuffers o_bufs;

	void HookPresent() {
		printf("[...] Hooking Present...\n");
		present = findDirect11Present();
		DetourTransactionBegin();
		DetourAttach(&(LPVOID&)present, hook_Present);
		DetourTransactionCommit();
		printf("[+] Hooked present at %p\n", present);
	}
	void HookResizeBuffers() {
		printf("[...] Hooking ResizeBuffers...\n");
		DetourTransactionBegin();
		DetourAttach(&(LPVOID&)o_bufs, hook_ResizeBuffers);
		DetourTransactionCommit();
		printf("[+] Hooked buffers at %p\n", o_bufs);
	}

	static IDXGISwapChainPresent findDirect11Present()
	{
		WNDCLASSEX wc{ 0 };
		wc.cbSize = sizeof(wc);
		wc.lpfnWndProc = DefWindowProc;
		wc.lpszClassName = TEXT("M");

		if (!RegisterClassEx(&wc))
		{
			return nullptr;
		}

		HWND hWnd = CreateWindow(wc.lpszClassName, TEXT(""), WS_DISABLED, 0, 0, 0, 0, NULL, NULL, NULL, nullptr);

		IDXGISwapChain* pSwapChain;

		D3D_FEATURE_LEVEL featureLevel;
		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		// Main D3D11 Objects
		ID3D11DeviceContext* pContext = nullptr;
		ID3D11Device* pDevice = nullptr;

		if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 1, D3D11_SDK_VERSION,
			&swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)) &&
			FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
				&swapChainDesc, &pSwapChain, &pDevice, &featureLevel, &pContext)))
		{
			DestroyWindow(swapChainDesc.OutputWindow);
			UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

			return nullptr;
		}

		const DWORD_PTR* pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChain);
		pSwapChainVtable = reinterpret_cast<DWORD_PTR*>(pSwapChainVtable[0]);

		auto swapChainPresent = reinterpret_cast<IDXGISwapChainPresent>(pSwapChainVtable[8]);
		o_bufs = reinterpret_cast<ResizeBuffers>(pSwapChainVtable[13]);

		pDevice->Release();
		pSwapChain->Release();

		DestroyWindow(swapChainDesc.OutputWindow);
		UnregisterClass(wc.lpszClassName, GetModuleHandle(nullptr));

		return swapChainPresent;
	}

	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
	{
		//// Load from disk into a raw RGBA buffer
		//int image_width = 0;
		//int image_height = 0;
		//unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
		//if (image_data == NULL)
		//	return false;

		//ID3D11SamplerState* pSamplerState = nullptr;
		//D3D11_SAMPLER_DESC samplerDesc;
		//ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		//samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		//samplerDesc.MaxAnisotropy = 16;
		//samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		//samplerDesc.MipLODBias = 1;
		//samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		//samplerDesc.BorderColor[0] = 0;
		//samplerDesc.BorderColor[1] = 0;
		//samplerDesc.BorderColor[2] = 0;
		//samplerDesc.BorderColor[3] = 0;
		//samplerDesc.MinLOD = 0;
		//samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		//pDevice->CreateSamplerState(&samplerDesc, &pSamplerState);
		//pContext->PSSetSamplers(0, 1, &pSamplerState);

		//// Create texture
		//D3D11_TEXTURE2D_DESC desc;
		//ZeroMemory(&desc, sizeof(desc));
		//desc.Width = image_width;
		//desc.Height = image_height;
		//desc.MipLevels = 1;
		//desc.ArraySize = 1;
		//desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//desc.SampleDesc.Count = 1;
		//desc.Usage = D3D11_USAGE_DEFAULT;
		//desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		//desc.CPUAccessFlags = 0;

		//ID3D11Texture2D* pTexture = NULL;
		//D3D11_SUBRESOURCE_DATA subResource;
		//subResource.pSysMem = image_data;
		//subResource.SysMemPitch = desc.Width * 4;
		//subResource.SysMemSlicePitch = 0;
		//pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		//// Create texture view
		//D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		//ZeroMemory(&srvDesc, sizeof(srvDesc));
		//srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		//srvDesc.Texture2D.MipLevels = desc.MipLevels;
		//srvDesc.Texture2D.MostDetailedMip = 0;
		//pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		//pTexture->Release();

		//*out_width = image_width;
		//*out_height = image_height;
		//stbi_image_free(image_data);

		return true;
	}
}