#pragma once
#include "../Frameworks/Json/json.hpp"
#include "../Frameworks/ImGui/ImGuiInclude.h"
#include "../Utils/Singleton.h"
#include <fstream>

template <typename T>
class ConfigField 
{
public:
    ConfigField(const std::string& path, std::string key, T val) : m_Value(val), m_Path(path), m_Key(key) {}
    ConfigField(const std::string& path, std::string key) : m_Path(path), m_Key(key) {}
    ConfigField() {}

    T& getValue() { return m_Value; }
    void setValue(T val) { m_Value = val; }

    operator T() { return m_Value; }

    std::string getPath() { return m_Path; }
    std::string getKey() { return m_Key; }

private:
    T m_Value = {};
    std::string m_Path;
    std::string m_Key;
};

struct ConfigFile 
{
    std::filesystem::path m_filePath = "";
    std::string m_Name = "";

    ConfigFile(const std::string& name, std::filesystem::path path) : m_Name(name), m_filePath(path) {};
    ConfigFile() {}
};

class ConfigManager : public Singleton<ConfigManager> 
{
public:
    void InitConfigFilesAtPath(std::filesystem::path path);
    std::map<int, std::pair<std::string, ConfigFile>> GetCurrentConfigFiles();
    bool CreateConfigFile(std::string filename);

    nlohmann::json& GetCurrentConfig();
    void ResetCurrentConfig();

    void LoadConfigFile(ConfigFile file);
    void UpdateConfigFile(ConfigFile file);
private:
    std::map<int, std::pair<std::string, ConfigFile>> m_ConfigFiles;
    nlohmann::json m_CurrentConfig;
};

namespace Config 
{
    namespace JsonUtils 
    {
        namespace 
        {
            std::vector<std::string> split(const std::string& content, const std::string& delimiter) {
                std::vector<std::string> tokens;
                size_t pos = 0;
                size_t prevPos = 0;
                std::string token;

                while ((pos = content.find(delimiter, prevPos)) != std::string::npos) {
                    token = content.substr(prevPos, pos - prevPos);
                    tokens.push_back(token);
                    prevPos = pos + delimiter.length();
                }

                tokens.push_back(content.substr(prevPos));
                return tokens;
            }
        }
    }

    namespace
    {
        void SaveConfig(nlohmann::json config)
        {
            std::filesystem::path authpath = std::string(getenv(("SystemDrive"))) + "\\";
            authpath = authpath / ("Minty-GI") / ("config.json");
            std::ofstream configFile(authpath);

            configFile << config.dump(4) << "\n";
            configFile.close();
        }
    }

    template <typename T>
    ConfigField<T> GetValue(std::string path, std::string key, const T& defaultValue) 
    {
        try 
        {
            nlohmann::json configRoot = ConfigManager::Instance().GetCurrentConfig();

            if (path.get().find(":") != std::string::npos) {
                auto sections = JsonUtils::split(path, ":");

                for (auto& section : sections)
                    configRoot = configRoot[section];

                if (configRoot.find(key) != configRoot.end()) {
                    return ConfigField<T>(path, key, configRoot[key]);
                }
            }

            if (configRoot.find(path) != configRoot.end() && configRoot[path].find(key) != configRoot[path].end()) {
                return ConfigField<T>(path, key, configRoot[path][key]);
            }
            return ConfigField<T>(path, key, defaultValue);
        }
        catch (nlohmann::json::exception e) 
        {
            return ConfigField<T>(path, key, defaultValue);
        }
    }

    template<typename T>
    void SetValue(std::string path, std::string key, const T& newValue) 
    {
        nlohmann::json& configRoot = ConfigManager::Instance().GetCurrentConfig();
        nlohmann::json* configTemp = &configRoot;
        if (path.get().find(":") != std::string::npos) {
            auto sections = JsonUtils::split(path, ":");
            for (auto& section : sections) {
                if (!configTemp->contains(section))
                    (*configTemp)[section] = {};

                configTemp = &(*configTemp)[section];
            }

            (*configTemp)[key] = newValue;
            return;
        }

        configRoot[path][key] = newValue;
    }

    template<typename T>
    void SetValue(ConfigField<T>& field, const T& newValue) 
    {
        SetValue(field.getPath(), field.getKey(), newValue);
    }
}

namespace  // Nameless namespace to prevent multi-definition errors 
{
    void ConfigCheckbox(const std::string& name, ConfigField<bool>& field) 
    {
        bool& value = field.getValue();

        if (ImGui::Checkbox(name.c_str(), &value)) {
            field.setValue(value);
            Config::SetValue(field, value);
        }
    }

    bool ConfigSliderFloat(const std::string& name, ConfigField<float>& field, float min, float max) 
    {
        float& value = field.getValue();

        if (ImGui::SliderFloat(name.c_str(), &value, min, max)) {
            field.setValue(value);
            Config::SetValue(field, value);
            return true;
        }
        return false;
    }

    void ConfigSliderInt(const std::string& name, ConfigField<int>& field, int min, int max) 
    {
        int& value = field.getValue();

        if (ImGui::SliderInt(name.c_str(), &value, min, max)) {
            field.setValue(value);
            Config::SetValue(field, value);
        }
    }
}
