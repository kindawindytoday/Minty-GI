#include "GraphicsChanger.h"

namespace Visuals {
	void hook_PostProcessLayer_Update(void* this_);

	void GraphicsChanger::InitConfig() {
		b_Gamma = Config::GetValue(this->m_Name, "gamma", false);
		f_GammaValue = Config::GetValue(this->m_Name, "gammaVal", 2.5f);

		b_Outline = Config::GetValue(this->m_Name, "outline", false);
		f_OutlineValue = Config::GetValue(this->m_Name, "outlineVal", 0.f);

		b_ResolutionScale = Config::GetValue(this->m_Name, "renderScale", false);
		f_ResolutionScaleValue = Config::GetValue(this->m_Name, "renderScaleVal", 0.5f);
	}

	void GraphicsChanger::InitHooks() {
		Hooks::Attach(Offsets::PostProcessLayer::Update, hook_PostProcessLayer_Update);
	}

	GraphicsChanger::GraphicsChanger() : Feature(
		"Graphics changer",
		"Changes some graphics settings")
	{
		InitConfig();
		InitHooks();
	}

	void GraphicsChanger::Options() {
		ConfigCheckbox("##Gamma", b_Gamma);				   ImGui::SameLine(); ConfigSliderFloat("Gamma", f_GammaValue, 0.f, 5.f);
		ConfigCheckbox("##Outline", b_Outline);			   ImGui::SameLine(); ConfigSliderFloat("Outline width", f_OutlineValue, 0.f, 5.f);
		ConfigCheckbox("##Resolution", b_ResolutionScale); ImGui::SameLine(); ConfigSliderFloat("Resolution scale", f_ResolutionScaleValue, 0.f, 3.f);
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNone)) {
			ImGui::BeginItemTooltip();
			ImGui::SetTooltip("Be careful! Values above 2.0 might crash your game on low-end PCs. Open and close game map to apply.");
			ImGui::EndTooltip();
		}

		if (ImGui::Button("Reset")) {
			f_GammaValue.setValue(2.0f); Config::SetValue(f_GammaValue, 2.0f);
			f_OutlineValue.setValue(1.0f); Config::SetValue(f_OutlineValue, 1.0f);
			f_ResolutionScaleValue.setValue(1.0f); Config::SetValue(f_ResolutionScaleValue, 1.0f);
		}
	}

	void GraphicsChanger::Status() {}

	void GraphicsChanger::OnUpdate() {}

	void GraphicsChanger::ProcessHotkeys() {}

	void hook_PostProcessLayer_Update(void* this_) {
		auto& instance = GraphicsChanger::Instance();

		if (instance.b_Gamma) {
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::_gammaValue) = instance.f_GammaValue;
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::_gammaValueChanged) = true;
		}

		if (instance.b_Outline) {
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::outlineCorrectionWidth) = instance.f_OutlineValue;
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::cameraBufferDirty) = true;
		}

		if (instance.b_ResolutionScale) {
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::m_InnerResolutionScale) = instance.f_ResolutionScaleValue;
			*reinterpret_cast<float*>((uintptr_t)this_ + Offsets::PostProcessLayer::Offsets::cameraBufferDirty) = true;
		}

		Hooks::Call(hook_PostProcessLayer_Update, this_);
	}
}