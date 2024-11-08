#define IMGUI_DEFINE_MATH_OPERATORS
#include "Layout.h"
#include <chrono>
#include "thread"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../Frameworks/ImGui/imgui_internal.h"

using namespace std::chrono_literals;

namespace Utils {
	void TextCentered(std::string text) {
		auto windowWidth = ImGui::GetWindowSize().x;
		auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
		ImGui::Text(text.c_str());
	}

	void AlignForWidth(float width, float alignment = 0.5f)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		float avail = ImGui::GetContentRegionAvail().x;
		float off = (avail - width) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}
}

namespace Pages {
	auto start_time = std::chrono::steady_clock::now();

	void PageLoading() {
		auto& window = MainWindow::Instance();
		auto& io = ImGui::GetIO();

		auto current_time = std::chrono::steady_clock::now();
		auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

		ImGui::Dummy({ -1, 80 });

		ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 115, 115, 255).operator ImVec4());
		ImGui::PushStyleColor(ImGuiCol_Text, { ImGui::GetStyleColorVec4(ImGuiCol_Text).x, ImGui::GetStyleColorVec4(ImGuiCol_Text).y, ImGui::GetStyleColorVec4(ImGuiCol_Text).z, float(elapsed_time / 1500.f) });
		Utils::TextCentered("Kinda Windy Today");
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		if (elapsed_time == 2000) {
			window.CurrentPage = PageIndex::PageMain;
		}
	}

	void PageMain() {
		auto& window = MainWindow::Instance();
		
		ImGui::Text("Minty!");
	}
}

void MainWindow::AddPage(Page page) {
	this->PagesMap[page.index] = page.code;
}

void MainWindow::DrawTabBar() {
	ImGui::SameLine(ImGui::GetWindowWidth() - 38.f);
	ImGui::SetCursorPosY(25);
	auto OriginalColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);
	ImGui::PushStyleColor(ImGuiCol_Button, { 0,0,0,0 });
	if (ImGui::SmallButton("X")) {
		this->Opened = false;
	}
	ImGui::PushStyleColor(ImGuiCol_Button, OriginalColor);
}

void MainWindow::DrawMain() {
	// DEBUG

	// Defines
	auto& io = ImGui::GetIO();

	// Drawing
	ImGui::SetNextWindowPos(this->WindowPos, ImGuiCond_Once, { 0.5, 0.5 });
	ImGui::SetNextWindowSize(this->WindowSize);

	ImGui::Begin("##Main", 0, this->mainWindowFlags);
	{
		// Tab bar
		//ImGui::PushFont(FontsLoader::Instance().FontsMap[Fonts::Jost::Regular::TitleBar]);
		this->DrawTabBar();
		//ImGui::PopFont();

		// Draw current page
		//ImGui::PushFont(FontsLoader::Instance().FontsMap[Fonts::Jost::Regular::MainText]);
		this->PagesMap[CurrentPage]();
		//ImGui::PopFont();
	}
	ImGui::End();

	//ImGui::ShowStyleEditor();
}

void MainWindow::InitWindow() {
	RECT ScreenRect{};
	GetWindowRect(GetDesktopWindow(), &ScreenRect);
	ImVec2 ScreenRes = ImVec2(float(ScreenRect.right), float(ScreenRect.bottom));

	this->WindowPos = (ScreenRes - this->WindowSize) * 0.5f;
	this->WindowSize = { 520, 630 };
	this->Opened = true;

	this->AddPage({ PageIndex::PageLoading, Pages::PageLoading });
	this->AddPage({ PageIndex::PageMain, Pages::PageMain });

	this->CurrentPage = PageIndex::PageLoading;

	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = ImColor(33, 33, 41, 255);
	style.Colors[ImGuiCol_PlotLines] = ImColor(255, 115, 115, 255);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(0, 0, 0, 0);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(0, 0, 0, 255);
	style.Colors[ImGuiCol_Button] = ImColor(0, 0, 0, 0);
	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 115, 115, 255);

	style.Colors[ImGuiCol_FrameBg] = ImColor(104, 104, 104, 162);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(82, 82, 82, 138);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(63, 63, 63, 138);

	style.Colors[ImGuiCol_Text] = ImColor(186, 186, 186, 255);

	style.Colors[ImGuiCol_Separator] = ImColor(0.200f, 0.200f, 0.200f, 1.000f);

	style.ChildRounding = 6;
	style.FrameRounding = 6;
	style.WindowRounding = 30;

	style.ScrollbarSize = 0;

	style.WindowBorderSize = 1;
	style.WindowPadding = { 54, style.WindowPadding.y };
}
