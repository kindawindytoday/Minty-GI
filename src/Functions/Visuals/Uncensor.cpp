#include "Uncensor.h"

namespace Visuals {
	void hook_UnknownPeeking(void* this_, void* a1, void* a2, void* a3);

	void Uncensor::InitConfig() {}

	void Uncensor::InitHooks() {
		Hooks::Attach(Offsets::Unknown::UnknownPeeking, hook_UnknownPeeking);
	}

	Uncensor::Uncensor() : Feature(
		"Remove censorship",
		"Removes camera censorship at certain angles")
	{
		InitConfig();
		InitHooks();
	}

	void Uncensor::Options() {}

	void Uncensor::Status() {}

	void Uncensor::OnUpdate() {}

	void Uncensor::ProcessHotkeys() {}

	void hook_UnknownPeeking(void* this_, void* a1, void* a2, void* a3) {
		auto& instance = Uncensor::Instance();
		if (instance.m_Enabled) return;

		Hooks::Call(hook_UnknownPeeking, this_, a1, a2, a3);
	}
}