#include "Settings.h"

namespace Settings {
	void Configs::InitConfig()
	{
		b_ShowFps = Config::GetValue(this->m_Name, ("showFps"), true);
		b_ShowStatus = Config::GetValue(this->m_Name, ("showStatus"), true);
		b_TpScreen = Config::GetValue(this->m_Name, ("showTpScreen"), true);

		h_OpenMenu = Hotkey(this->m_Name, ("openMenu"), ImGuiKey_F12);
	}

	void Configs::InitHooks() 
	{
		std::filesystem::path filespath = std::string(getenv(("SystemDrive"))) + "\\";
		filespath = filespath / ("Minty-GI") / ("configs");

		ConfigManager::Instance().InitConfigFilesAtPath(filespath);
	}

	Configs::Configs() : Feature(
		("Settings"),
		("---"))
	{
		InitConfig();
		InitHooks();
	}

	static int currentConfig = -1;
	void Configs::Options() 
	{
		ImGui::SeparatorText(("Menu"));
		h_OpenMenu.Draw(("Menu open key"));
		ConfigCheckbox(("Show FPS counter"), b_ShowFps);
		ConfigCheckbox(("Show function status"), b_ShowStatus);
		ConfigCheckbox(("Show TP loading screen"), b_TpScreen);

		ImGui::SeparatorText(("Configs"));

		if (ImGui::Button(("Reset config"))) {
			ConfigManager::Instance().ResetCurrentConfig();
			for (auto& module : FeatureManager::Instance().GetModules()) {
				for (auto& func : module.GetFeatures()) {
					func->m_Enabled = Config::GetValue(func->m_Name, ("enabled"), false);
					func->h_Enable = Hotkey(func->m_Name, ("enable"));
					func->InitConfig();
				}
			}
			currentConfig = -1;
		} ImGui::SameLine();

		static std::string createBuf = "";
		if (ImGui::BeginPopup(("##21"))) {
			ImGui::SetNextItemWidth(100);
			ImGui::InputText(("Config name"), &createBuf);
			if (ImGui::Button(("Create"))) {
				ConfigManager::Instance().CreateConfigFile(createBuf);
				ImGui::CloseCurrentPopup();

				std::filesystem::path filespath = std::string(getenv(("SystemDrive"))) + "\\";
				filespath = filespath / ("Minty-GI") / ("configs");
				ConfigManager::Instance().InitConfigFilesAtPath(filespath);
			}
			ImGui::EndPopup();
		}

		if (ImGui::Button(("Create config"))) {
			createBuf = "";
			ImGui::OpenPopup(("##21"));
		}

		ImGui::BeginChild(("Loaded configs"), {-1, -1});
		{
			auto files = ConfigManager::Instance().GetCurrentConfigFiles();
			for (int i = 0; i < files.size(); i++) {
				auto& file = files[i];
				if (currentConfig == i) {
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::ColorConvertU32ToFloat4(0xFF806E6F));
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::ColorConvertU32ToFloat4(0xFF3C3736));
				}
				ImGui::BeginChild(std::string("##" + file.first).c_str(), { -1, 50 });
				float tempPos = ImGui::GetCursorPosY();
				ImGui::SetCursorPosY(tempPos + 33 / 2);
				ImGui::BeginChild("##22", { 200, -1 });

				ImGui::Text(("	Name: %s"), file.first.c_str());

				ImGui::EndChild();

				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 16);
				ImGui::SameLine();
				ImGui::Dummy({ 170, 0 });
				ImGui::SameLine();

				ImGui::BeginGroup();
				if (currentConfig == i) {
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
					if (ImGui::Button(("Save"), {90, 33})) {
						ConfigManager::Instance().UpdateConfigFile(file.second);
					}
				}
				else {
					ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
					if (ImGui::Button(("Load"), {90, 33})) {
						ConfigManager::Instance().LoadConfigFile(file.second);
						for (auto& module : FeatureManager::Instance().GetModules()) {
							for (auto& func : module.GetFeatures()) {
								func->m_Enabled = Config::GetValue(func->m_Name, ("enabled"), false);
								func->h_Enable = Hotkey(func->m_Name, ("enable"));
								func->InitConfig();
							}
						}
						currentConfig = i;
					}
				} ImGui::SameLine();

				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8);
				if (ImGui::Button(("Delete"), {90, 33})) {
					std::filesystem::remove(file.second.m_filePath);

					std::filesystem::path filespath = std::string(getenv(("SystemDrive"))) + "\\";
					filespath = filespath / ("Minty-GI") / ("configs");
					ConfigManager::Instance().InitConfigFilesAtPath(filespath);

					currentConfig = -1;
				}
				ImGui::EndGroup();

				ImGui::EndChild();
				ImGui::PopStyleColor();
			}
		}
		ImGui::EndChild();
	}

	void Configs::Status() {}

	void Configs::OnUpdate() {}

	void Configs::ProcessHotkeys() {}
}