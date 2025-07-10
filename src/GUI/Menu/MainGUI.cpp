#include "MainGUI.h"

void TextCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
	ImGui::Text(text.c_str());
}

void HelpMarker(const char* description) {
	ImGui::TextDisabled(("(?)"));

	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(description);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool IsSpecialFunction(Feature* func) {
	if (func->m_Name == ("Settings")) return true; else return false;
}

const void Menu::DrawFrame()
{
	//ImGui::ShowStyleEditor();
	//ImGui::ShowMetricsWindow();

	auto& instance = FeatureManager::Instance();
	static int currentModule = 0;
	static int currentFunction = 0;

	auto _currentModule = instance.GetModules()[currentModule];
	auto _currentFunction = _currentModule.GetFeatures()[currentFunction];
	
	ImGui::SetNextWindowSize({ 835, 620 });
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2 }, ImGuiCond_FirstUseEver, {0.5, 0.5});
	ImGui::Begin(("##1"), nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);
	{
		auto image = ImageLoader::Instance().ImagesMap[105];
		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0,0,0,0 });
		ImGui::BeginChild(("##2"), {50, 50});
		{
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
			ImGui::Image((ImTextureID)image.srv, ImVec2{ (float)image.width, (float)image.height }); ImGui::SameLine();
		}
		ImGui::PopStyleColor();
		ImGui::EndChild();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			ImGui::GetCurrentContext()->MovingWindow = ImGui::GetCurrentWindow(); 
		
		ImGui::SameLine();

		ImGui::BeginChild(("##3"), {-1, 50}, ImGuiChildFlags_FrameStyle);
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(("MINTY GI | KINDA WINDY TODAY | 5.4.0.0")).x) / 3));
			ImGui::Text(("MINTY GI | KINDA WINDY TODAY | 5.7.0.4")); ImGui::SameLine();
			
			auto time = std::time(nullptr);
			std::stringstream ss;
			ss << std::put_time(std::localtime(&time), ("%H:%M"));
			ImGui::Text(("    %s"), ss.str().c_str()); ImGui::SameLine();
		}
		ImGui::EndChild();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			ImGui::GetCurrentContext()->MovingWindow = ImGui::GetCurrentWindow();
		
		ImGui::BeginGroup();

		if (ImGui::BeginListBox(("##4"), {225, -FLT_MIN}))
		{
			auto modules = instance.GetModules();
			for (int i = 0; i < modules.size(); i++) {
				auto module = modules[i];
				auto features = module.GetFeatures();

				if (ImGui::CollapsingHeader(module.GetName().c_str()))
				{
					for (int j = 0; j < features.size(); j++)
					{
						auto func = features[j];

						ImGui::PushStyleColor(ImGuiCol_Header, 0xFF4F4F4F);
						ImGui::PushStyleColor(ImGuiCol_HeaderHovered, 0xFF3F3F3F);
						ImGui::PushStyleColor(ImGuiCol_HeaderActive, 0xFF2F2F2F);
						ImGui::PushID((long long)func);
						if (ImGui::Selectable(std::string(func->m_Name).c_str(), j == currentFunction && i == currentModule, 0)) {
							currentModule = i;
							currentFunction = j;
						}
						ImGui::PopID();
						ImGui::PopStyleColor();
						ImGui::PopStyleColor();
						ImGui::PopStyleColor();
					}
				}

			}

			ImGui::EndListBox();
		}

		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!IsSpecialFunction(_currentFunction)) {
			ImGui::BeginChild(("##5"), { -1, 55 }, ImGuiChildFlags_FrameStyle);
			{
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{ 63.f / 255.f, 63.f / 255.f, 63.f / 255.f, 1.0 });
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 63.f / 255.f, 63.f / 255.f, 63.f / 255.f, 1.0 });

				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 6);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 12);
				HelpMarker(_currentFunction->m_Description.c_str()); ImGui::SameLine();
				ImGui::Text(_currentFunction->m_Name.c_str());
				ImGui::SameLine();
				ConfigCheckbox("##11", _currentFunction->m_Enabled); ImGui::SameLine(); ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical); ImGui::SameLine();
				_currentFunction->h_Enable.Draw();

				ImGui::PopStyleColor();
				ImGui::PopStyleColor();
			}
			ImGui::EndChild();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
				ImGui::GetCurrentContext()->MovingWindow = ImGui::GetCurrentWindow();
		}

		ImGui::BeginChild(("##6"), { -1, -1 }, ImGuiChildFlags_FrameStyle);
		{
			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{ 63.f / 255.f, 63.f / 255.f, 63.f / 255.f, 1.0 });
			
			if (!_currentFunction->m_Enabled && !IsSpecialFunction(_currentFunction)) ImGui::BeginDisabled();
			_currentFunction->Options();
			if (!_currentFunction->m_Enabled && !IsSpecialFunction(_currentFunction)) ImGui::EndDisabled();

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left))
			ImGui::GetCurrentContext()->MovingWindow = ImGui::GetCurrentWindow();

		ImGui::EndGroup();
	}
	ImGui::End();
}

const void Menu::DrawStatus()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 8,8 });
	ImGui::SetNextWindowPos({ 100,150 }, ImGuiCond_FirstUseEver);
	ImGui::Begin(("##7"), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text(("Active functions:"));
	auto& manager = FeatureManager::Instance();
	if (ImGui::BeginTable(("#8"), 1, ImGuiTableFlags_Borders))
	{
		for (auto& module : manager.GetModules()) {
			for (auto& feature : module.GetFeatures()) {
				if (feature->m_Enabled) {
					if (IsSpecialFunction(feature)) continue;
					ImGui::TableNextColumn();
					ImGui::Text(feature->m_Name.c_str());
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::End();
	ImGui::PopStyleVar();
}

const void Menu::DrawFPS()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 8,8 });
	ImGui::SetNextWindowPos({ 100,100 }, ImGuiCond_FirstUseEver);
	ImGui::Begin(("##FPS"), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
	ImGui::Text(("Minty GI | FPS: %i"), (int)ImGui::GetIO().Framerate);
	ImGui::End();
	ImGui::PopStyleVar();
}

const void Menu::ExecuteHotkeys()
{
	const auto& manager = FeatureManager::Instance();
	for (auto& module : manager.Instance().GetModules()) {
		for (auto& feature : module.GetFeatures()) {
			if (feature->h_Enable.IsPressed()) {
				Config::SetValue(feature->m_Enabled, !feature->m_Enabled);
				feature->m_Enabled.setValue(!feature->m_Enabled); // process general function toggle here to avoid excessive code in every func::ProcessHotkeys
			}
			feature->ProcessHotkeys();
		}
	}
}

const void Menu::ExecuteOuter()
{
	auto& instance = FeatureManager::Instance();
	for (auto& module : instance.GetModules()) {
		for (auto& feature : module.GetFeatures()) {
			feature->OnUpdate();
		}
	}
}

void Menu::DrawTeleportingScreen()
{
	auto pos = ImGui::GetMainViewport()->Pos;
	auto size = ImGui::GetMainViewport()->Size;

	ImColor col = IM_COL32(11, 14, 18, 250);
	col.Value.w = this->f_TeleportingAlpha;

	ImGui::GetBackgroundDrawList()->AddRectFilled(
		pos,
		pos + size,
		col, // Red color (RGBA)
		0.0f, // Rounding
		0 // Flags
	);

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin(("##9"), nullptr,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoBackground);

	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	ImVec2 buttonSize(100.0f, 100.0f);
	ImVec2 centerPos(
		(screenSize.x - buttonSize.x) * 0.5f,
		(screenSize.y - buttonSize.y) * 0.5f
	);

	ImGui::SetCursorPos(centerPos - ImVec2{50,50});
	ImGui::Spinner(("##10"), 100, 2, IM_COL32(239, 105, 105, 255));

	ImGui::End();
}
