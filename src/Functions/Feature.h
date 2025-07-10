#pragma once
#include <string>
#include "../GUI/Menu/Hotkey.h"
#include "../Config/ConfigManager.h"

class Feature 
{
public:
	std::string m_Name;
	std::string m_Description;

	Hotkey h_Enable;

	ConfigField<bool> m_Enabled;

	virtual void Options()        {};
	virtual void Status()         {};
	virtual void OnUpdate()       {};
	virtual void ProcessHotkeys() {};

	virtual void InitConfig()     {};
	virtual void InitHooks()      {};

	Feature(const char* name, const char* description)
	{
		m_Name = std::string(name);
		m_Description = std::string(description);

		m_Enabled = Config::GetValue(name, ("enabled"), false);
		h_Enable = Hotkey(name, ("enable"));
	}
};