#define STB_IMAGE_IMPLEMENTATION
#include "InitGui.h"

HWND g_hwnd = 0;
namespace GUI {
	LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
		if (msg == WM_CLOSE) {
			__fastfail(0);
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}

		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
			return true;
		}

		switch (msg) {
		case WM_SIZE:
			if (pd3dDevice != nullptr && wparam != SIZE_MINIMIZED) {
				CleanupRenderTarget();
				pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lparam), (UINT)HIWORD(wparam), DXGI_FORMAT_UNKNOWN, 0);
				CreateRenderTarget();
			}
			return 0;
		case WM_SYSCOMMAND:
			if ((wparam & 0xfff0) == SC_KEYMENU) {
				return 0;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_DPICHANGED: {
			const RECT* rect = (RECT*)lparam;
			SetWindowPos(hwnd, nullptr, rect->left, rect->top, rect->right - rect->left, rect->bottom - rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
		}
		case WM_CLOSE:
			return DefWindowProc(hwnd, msg, wparam, lparam);
			break;
		default:
			break;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	bool CreateDevice(HWND hwnd) {
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 2;
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hwnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		const UINT createDeviceFlags = 0;

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
		if (D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pd3dDeviceContext) != S_OK)
			return false;

		CreateRenderTarget();
		return true;
	}

	void CleanupDevice() {
		CleanupRenderTarget();
		if (pSwapChain)
		{
			pSwapChain->Release();
			pSwapChain = nullptr;
		}

		if (pd3dDeviceContext)
		{
			pd3dDeviceContext->Release();
			pd3dDeviceContext = nullptr;
		}

		if (pd3dDevice)
		{
			pd3dDevice->Release();
			pd3dDevice = nullptr;
		}
	}

	void CreateRenderTarget() {
		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer != nullptr)
		{
			pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pMainRenderTargetView);
			pBackBuffer->Release();
		}
	}

	void CleanupRenderTarget() {
		if (pMainRenderTargetView)
		{
			pMainRenderTargetView->Release();
			pMainRenderTargetView = nullptr;
		}
	}

	void Init() {
		ImGui_ImplWin32_EnableDpiAwareness();
		const WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, GetModuleHandle(0), LoadIconA(GetModuleHandle(0), MAKEINTRESOURCEA(110)), 0, 0, 0, L"Minty", 0 };
		RegisterClassEx(&wc);

		const HWND hwnd = CreateWindowW(wc.lpszClassName, L"Minty", WS_POPUP, 0, 0, 5, 5, 0, 0, wc.hInstance, 0);
		Globals::Instance().g_Hwnd = hwnd;

		if (!CreateDevice(hwnd)) {
			CleanupDevice();
			UnregisterClass(wc.lpszClassName, wc.hInstance);
			return;
		}

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);

		ImGui::CreateContext();
		auto& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.IniFilename = nullptr;

		ResourceLoader::Instance().SetHandle(GetModuleHandleA(0));

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(pd3dDevice, pd3dDeviceContext);
		ImGui_ImplWin32_EnableAlphaCompositing(Globals::Instance().g_Hwnd);

		MainWindow::Instance().InitWindow();

		while (Render());

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		CleanupDevice();
		DestroyWindow(hwnd);
		UnregisterClass(wc.lpszClassName, wc.hInstance);

		__fastfail(0);
	}

	// bool Render() -- returns false if app is about to exit, so Init() loop can go to the Shutdown part
	bool Render() {
		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}

			auto& io = ImGui::GetIO();
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			MainWindow::Instance().DrawMain();

			ImGui::EndFrame();
			ImGui::Render();

			const float clear_color[4] = { 0, 0, 0, 0 };
			pd3dDeviceContext->OMSetRenderTargets(1, &pMainRenderTargetView, nullptr);
			pd3dDeviceContext->ClearRenderTargetView(pMainRenderTargetView, clear_color);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
			}

			pSwapChain->Present(1, 0);

			if (!MainWindow::Instance().Opened) msg.message = WM_QUIT;
		}
		return false;
	}

	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
	{
		// Load from disk into a raw RGBA buffer
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

		pd3dDevice->CreateSamplerState(&samplerDesc, &pSamplerState);
		pd3dDeviceContext->PSSetSamplers(0, 1, &pSamplerState);

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
		pd3dDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		pd3dDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}
}