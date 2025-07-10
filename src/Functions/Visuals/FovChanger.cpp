#include "FovChanger.h"

namespace Visuals {
	void hook_set_fieldOfView(Unity::Camera* this_, float value);

	void FovChanger::InitConfig() {
		f_Fov = Config::GetValue(this->m_Name, "fov", 75.f);
	}

	void FovChanger::InitHooks() {
		Hooks::Attach(Offsets::Camera::set_fieldOfView, hook_set_fieldOfView);
	}

	FovChanger::FovChanger() : Feature(
		"FOV changer",
		"Changes camera field of view")
	{
		InitConfig();
		InitHooks();
	}

	void FovChanger::Options() {
		ConfigSliderFloat("Target FOV", f_Fov, 10, 150);
	}

	void FovChanger::Status() {}

	void FovChanger::OnUpdate() {}

	void FovChanger::ProcessHotkeys() {}

	void hook_set_fieldOfView(Unity::Camera* this_, float value) {
		auto& instance = FovChanger::Instance();

		if (instance.m_Enabled)
			value = instance.f_Fov;

		Hooks::Call(hook_set_fieldOfView, this_, value);
	}
}