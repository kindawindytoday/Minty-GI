#pragma once

#include <Windows.h>
#include "../../Frameworks/ImGui/ImGuiInclude.h"
#include "../../Config/ConfigManager.h"

class Hotkey {
public:
	ConfigField<ImGuiKey> key;

	bool IsDown();
	bool IsPressed();

	void Draw(std::string text = "");

	Hotkey() {}

	Hotkey(std::string _path, std::string _name) {
		key = Config::GetValue(_path, _name, ImGuiKey_None);
	}

	Hotkey(std::string _path, std::string _name, ImGuiKey _key) {
		key = Config::GetValue(_path, _name, _key);
	}

private:
	void UpdateKey();
	std::string GetDrawText();
	bool IsUpdating = false;
};