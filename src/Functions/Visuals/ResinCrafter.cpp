#include "ResinCrafter.h"

namespace Visuals {
	void RequestCraftResin(int count);

	void ResinCrafter::InitConfig() {
		i_ResinPieces = Config::GetValue(this->m_Name, "resin", 5);
	}

	void ResinCrafter::InitHooks() {}

	ResinCrafter::ResinCrafter() : Feature(
		"Resin crafter",
		"Remotely crafts X pcs. of 'Condensed Resin'.\nNote: you must have enough resources")
	{
		InitConfig();
		InitHooks();
	}

	void ResinCrafter::Options() {
		ConfigSliderInt("Resin pieces", i_ResinPieces, 1, 5);
		if (ImGui::Button("Craft")) {
			RequestCraftResin(i_ResinPieces);
		}
	}

	void ResinCrafter::Status() {}

	void ResinCrafter::OnUpdate() {}

	void ResinCrafter::ProcessHotkeys() {}

	void RequestCraftResin(int count) {
		// ¯\_(ツ)_/¯
	}
}