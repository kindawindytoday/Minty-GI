#include "ConfigManager.h"

void ConfigManager::InitConfigFilesAtPath(std::filesystem::path path)
{
	std::map<int, std::pair<std::string, ConfigFile>> ret;

	if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
		int i = 0;
		for (auto& file : std::filesystem::directory_iterator(path)) {
			if (file.path().filename().string().ends_with((".json"))) {
				ret[i] = { file.path().filename().string(), ConfigFile(file.path().filename().string(), file.path()) };
				i++;
			}
		}
	}

	this->m_ConfigFiles = ret;
}

std::map<int, std::pair<std::string, ConfigFile>> ConfigManager::GetCurrentConfigFiles()
{
	return this->m_ConfigFiles;
}

bool ConfigManager::CreateConfigFile(std::string filename)
{
	if (filename == "") return false;

	std::filesystem::path filespath = std::string(getenv(("SystemDrive"))) + "\\";
	filespath = filespath / ("Minty-GI") / ("configs");

	if (!std::filesystem::is_directory(filespath) || !std::filesystem::exists(filespath)) {
		std::filesystem::create_directories(filespath);
	}

	auto files = this->m_ConfigFiles;

	for (auto& file : files) {
		if (file.second.first == filename) {
			return false;
		}
	}
	std::ofstream created(filespath / (filename + (".json")));
	created << this->m_CurrentConfig;
	created.close();

	return true;
}

nlohmann::json& ConfigManager::GetCurrentConfig()
{
	return this->m_CurrentConfig;
}

void ConfigManager::ResetCurrentConfig()
{
	this->m_CurrentConfig.clear();
}

void ConfigManager::LoadConfigFile(ConfigFile file)
{
	std::ifstream configfile(file.m_filePath);
	nlohmann::json configjson;
	configfile >> configjson;
	this->m_CurrentConfig = configjson;

	configfile.close();
}

void ConfigManager::UpdateConfigFile(ConfigFile file)
{
	std::ofstream configfile(file.m_filePath, std::ofstream::trunc);
	configfile << this->m_CurrentConfig;

	configfile.close();
}