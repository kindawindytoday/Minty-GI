#include "InitGUI.h"
#include "../DirectX/DirectXHook.h"
#include "../../../resource.h"
#include "../../Functions/Settings/Settings.h"
#include "../../Frameworks/ImGui/imgui_freetype.h"

const void GUI::Init(HWND window, ID3D11Device* device, ID3D11DeviceContext* context) {
	printf(("[...] ImGui bootstrapping\n"));

	ImGui::CreateContext();
	ImGui_ImplWin32_EnableDpiAwareness();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(device, context);

	printf(("[+] ImGui bootstrapped succesfully\n"));

	ImGui::GetIO().IniFilename = nullptr;
	ImGui::GetIO().MouseDrawCursor = false;

	ImFontConfig config = {};

	FontsLoader::Instance().LoadFont(IDR_RCDATA3, 20.f, &config, 345, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	FontsLoader::Instance().LoadFont(IDR_RCDATA1, 20.f, &config, Fonts::Kodchasan::Bold::a20, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	FontsLoader::Instance().LoadFont(IDR_RCDATA1, 16.f, &config, Fonts::Kodchasan::Bold::a16, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	FontsLoader::Instance().LoadFont(IDR_RCDATA1, 24.f, &config, Fonts::Kodchasan::Bold::a24, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	FontsLoader::Instance().LoadFont(IDR_RCDATA2, 24.f, &config, Fonts::Kodchasan::Regular::a24, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	FontsLoader::Instance().LoadFont(IDR_RCDATA2, 18.f, &config, Fonts::Kodchasan::Regular::a16, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	FontsLoader::Instance().LoadFont(IDR_RCDATA2, 20.f, &config, Fonts::Kodchasan::Regular::a20, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	ImageLoader::Instance().LoadImageFromResources(IDB_PNG1);
	ImageLoader::Instance().LoadImageFromResources(IDB_PNG2);

	ImVec4* colors = ImGui::GetStyle().Colors;

	colors[ImGuiCol_Border] = ImVec4(0.98f, 0.49f, 0.55f, 1.00f);
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.089f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.129f, 0.129f, 0.161f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.13f, 0.13f, 0.16f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.29f, 0.48f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.83f, 0.59f, 0.62f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.83f, 0.59f, 0.62f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.73f, 0.52f, 0.54f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.98f, 0.49f, 0.55f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.71f, 0.50f, 0.53f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.87f, 0.63f, 0.66f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.98f, 0.49f, 0.55f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.71f, 0.50f, 0.53f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.87f, 0.63f, 0.66f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.98f, 0.49f, 0.55f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5, 3 });
	ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 8);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10);
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 5);
	ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 5);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 6,4 });
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_SeparatorTextAlign, { 0.5, 0.5 });

	Menu::Instance().b_Opened = true;
}

const void GUI::Render()
{
	static bool isVisible = true;
	static int32_t lockState = 0;

	Menu& menu = Menu::Instance();
	if (Settings::Configs::Instance().h_OpenMenu.IsPressed()) {
		menu.b_Opened = !menu.b_Opened;
		if (menu.b_Opened == true) {
			isVisible = Offsets::Cursor::get_visible();
			lockState = Offsets::Cursor::get_lockState();

			Offsets::Cursor::set_visible(true);
			Offsets::Cursor::set_lockState(0);
		}
		else {
			Offsets::Cursor::set_visible(isVisible);
			Offsets::Cursor::set_lockState(lockState);
		}
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();

	static double startTime = ImGui::GetTime();
	static bool prevShowMenu = menu.b_Opened;
	const float animDuration = 0.13f;

	if (menu.b_Opened != prevShowMenu)
	{
		startTime = ImGui::GetTime();
		prevShowMenu = menu.b_Opened;
	}

	float alpha = menu.b_Opened
		? min(1.0f, (ImGui::GetTime() - startTime) / animDuration)
		: max(0.0f, 1.0f - (ImGui::GetTime() - startTime) / animDuration);

	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
	if (menu.b_Opened || alpha > 0.f) 
	{
		auto mousePos = ImGui::GetMousePos();
		auto img = ImageLoader::Instance().ImagesMap[IDB_PNG2];
		ImGui::GetForegroundDrawList()->AddImage((ImTextureID)img.srv, mousePos, mousePos + ImVec2{ 26, 26 });

		menu.DrawFrame();
	}
	ImGui::PopStyleVar();

	if (Settings::Configs::Instance().b_ShowFps) menu.DrawFPS();
	if (Settings::Configs::Instance().b_ShowStatus) menu.DrawStatus();

	menu.ExecuteHotkeys();
	menu.ExecuteOuter();

	static double startTime2 = ImGui::GetTime();
	static bool prevShowMenu2 = menu.b_Teleporting;
	const float animDuration2 = 0.22f;

	if (menu.b_Teleporting != prevShowMenu2)
	{
		startTime2 = ImGui::GetTime();
		prevShowMenu2 = menu.b_Teleporting;
	}

	menu.f_TeleportingAlpha = menu.b_Teleporting
		? min(1.0f, (ImGui::GetTime() - startTime2) / animDuration2)
		: max(0.0f, 1.0f - (ImGui::GetTime() - startTime2) / animDuration2);

	if (Settings::Configs::Instance().b_TpScreen && (menu.b_Teleporting || menu.f_TeleportingAlpha > 0.f)) 
	{
		menu.DrawTeleportingScreen();
	}

	ImGui::RenderNotifications();
	ImGui::Render();
}
