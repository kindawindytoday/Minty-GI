#include "Hotkey.h"

bool Hotkey::IsDown() {
	return (this->IsUpdating || this->key.getValue() == ImGuiKey_None) ? false : ImGui::IsKeyDown(this->key.getValue());
}

bool Hotkey::IsPressed() {
	return (this->IsUpdating || this->key.getValue() == ImGuiKey_None) ? false : ImGui::IsKeyPressed(this->key.getValue(), false);
}

void Hotkey::Draw(std::string text) {
	ImGui::PushID(this);

	float buttonWidth = ImGui::CalcTextSize(GetDrawText().c_str()).x;
	if (buttonWidth < 55.f)
		buttonWidth = 55.f;

	if (ImGui::Button(GetDrawText().c_str(), {buttonWidth, 25.f})) {
		this->IsUpdating = true;
	}
	ImGui::PopID();

	ImGui::SameLine();
	
	ImGui::PushID(this + 10);
	if (ImGui::SmallButton("x")) {
		this->IsUpdating = false;
		Config::SetValue(this->key, ImGuiKey_None);
		this->key.setValue(ImGuiKey_None);
	}
	ImGui::PopID();
	
	ImGui::SameLine();
	if (text == "") {
		ImGui::Text("Hotkey");
	}
	else {
		ImGui::Text(text.c_str());
	}

	if (this->IsUpdating) {
		this->UpdateKey();
	}
}

void Hotkey::UpdateKey() {
	for (ImGuiKey key = ImGuiKey_NamedKey_BEGIN; key < ImGuiKey_NamedKey_END; key = (ImGuiKey)(key + 1)) {
		if (key == ImGuiKey_MouseLeft			|| 
			key == ImGuiKey_MouseRight			||
			key == ImGuiKey_MouseWheelY			||
			key == ImGuiKey_MouseWheelX			||
			key == ImGuiKey_GamepadLStickLeft   ||
			key == ImGuiKey_GamepadLStickRight	||
			key == ImGuiKey_GamepadLStickUp 	||
			key == ImGuiKey_GamepadLStickDown	||
			key == ImGuiKey_GamepadRStickLeft	||
			key == ImGuiKey_GamepadRStickRight	||
			key == ImGuiKey_GamepadRStickUp  	||
			key == ImGuiKey_GamepadRStickDown) continue;

		if (ImGui::IsKeyReleased(key)) {
			this->IsUpdating = false;
			Config::SetValue(this->key, key);
			this->key.setValue(key);
		}
	}
}

std::string Hotkey::GetDrawText() {
	if (IsUpdating)
		return std::string("...");
	else
		return std::string(ImGui::GetKeyName(this->key));
}
