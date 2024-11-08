#include "InitGUI.h"
#include "../DirectX/DirectXHook.h"

const void GUI::Init(HWND window, ID3D11Device* device, ID3D11DeviceContext* context) {
	printf("[...] ImGui bootstrapping\n");
	ImGui::CreateContext();
	printf("[+] CTX created\n");
	ImGui_ImplWin32_EnableDpiAwareness();
	ImGui_ImplWin32_Init(window);
	printf("[+] Win32 backend initializated on HWND %p\n", window);
	ImGui_ImplDX11_Init(device, context);
	printf("[+] DX11 backend initializated on dvc %p & ctx %p\n", device, context);
	printf("[+] ImGui bootstrapped succesfully\n");

	ImFontConfig font_cfg;
	//FontsLoader::Instance().LoadFont(ProjectGlobals::Instance().mainFontResourceNum, 18.f, &font_cfg, Fonts::Jost::Regular::Header, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	ImFontConfig config;
	config.MergeMode = true;
	config.GlyphMinAdvanceX = 16.0f;
	config.GlyphMaxAdvanceX = 16.0f;
	static const ImWchar icon_ranges[] = { 0xe000, 0xf8ff, 0 };
	//FontsLoader::Instance().LoadFont(ProjectGlobals::Instance().iconFontResourceNum, 16.f, &config, 333, icon_ranges);

	//ImageLoader::Instance().LoadImageFromResources(ProjectGlobals::Instance().logoResourceNum);

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
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
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
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
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

	Menu::Instance().b_Opened = true;

	Menu::Instance().StartOuter();
}

const void GUI::Render()
{
	Menu& menu = Menu::Instance();
	/*if (Settings::General::Instance().OpenMenuKey.IsPressed()) {
		menu.b_Opened = !menu.b_Opened;
	}*/
	menu.b_Opened = true;
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();
	static double startTime = ImGui::GetTime();
	static bool prevShowMenu = menu.b_Opened;
	const float animDuration = 0.13f;
	if (menu.b_Opened != prevShowMenu) {
		startTime = ImGui::GetTime();
		prevShowMenu = menu.b_Opened;
	}
	float alpha = menu.b_Opened
		? min(1.0f, (ImGui::GetTime() - startTime) / animDuration)
		: max(0.0f, 1.0f - (ImGui::GetTime() - startTime) / animDuration);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
	if (menu.b_Opened || alpha > 0.f) {
		menu.DrawFrame();
	}
	ImGui::PopStyleVar();
	//if (Settings::Appearance::Instance().IfShowFps()) menu.DrawFPS();
	//if (Settings::Appearance::Instance().IfShowStatus()) menu.DrawStatus();
	menu.ExecuteHotkeys();
	menu.ExecuteOverlay();
	ImGui::RenderNotifications();
	ImGui::Render();
}
