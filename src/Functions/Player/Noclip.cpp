#include "Noclip.h"

#define UNSAFE

namespace Player {
	void OnUpdate_Noclip();

	void Noclip::InitConfig() {
		b_UseAltSpeed = Config::GetValue(this->m_Name, ("useAltSpeed"), false);
		f_Speed = Config::GetValue(this->m_Name, ("speed"), 5.f);
		f_AltSpeed = Config::GetValue(this->m_Name, ("altSpeed"), 10.f);
	}

	void Noclip::InitHooks() {
#ifdef UNSAFE
		// ¯\_(ツ)_ /¯
#endif
	}

	Noclip::Noclip() : Feature(
		("Noclip"),
		("Lets you fly"))
	{
		InitConfig();
		InitHooks();
	}

	void Noclip::Options() {
		ConfigSliderFloat(("Speed"), f_Speed, 1.f, 20.f);
		ConfigCheckbox(("Use alt. speed"), b_UseAltSpeed);
		if (b_UseAltSpeed) {
			ImGui::Indent();
			ConfigSliderFloat(("Alt. Speed"), f_AltSpeed, 1.f, 20.f);
			ImGui::Unindent();
		}
	}

	void Noclip::Status() {}

	void Noclip::OnUpdate() {}

	void Noclip::ProcessHotkeys() {}

	void OnUpdate_Noclip()
	{
		auto& instance = Noclip::Instance();

		if (!MoleMole::LoadingManager::get_LoadingManager()->IsLoaded()) return;

		if (instance.m_Enabled) 
		{
			static auto start_time = std::chrono::steady_clock::now();

			auto current_time = std::chrono::steady_clock::now();
			auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();

			if (elapsed_time > 1000)
			{
				instance.cachedMgr = MoleMole::EntityManager::get_EntityManager();
				if (instance.cachedMgr == nullptr)
					return;

				auto mgr = (MoleMole::EntityManager*)instance.cachedMgr;
				instance.cachedAvatar = mgr->avatar();
				if (instance.cachedAvatar == nullptr)
					return;

				instance.cachedCamera = Offsets::Camera::get_main();
				if (instance.cachedCamera == nullptr)
					return;

				instance.cachedRelativeTransform = Offsets::Component::get_transform(instance.cachedCamera);
				if (instance.cachedRelativeTransform == nullptr)
					return;
#ifdef UNSAFE
				// ¯\_(ツ)_/¯
#endif
				start_time = std::chrono::steady_clock::now();
			}

			Unity::Vector3 dir = { 0,0,0 };

			auto avatar = (MoleMole::BaseEntity*)instance.cachedAvatar;
			if (avatar == nullptr) return;

			auto relativeTransform = (Unity::Transform*)instance.cachedRelativeTransform;
			if (relativeTransform == nullptr) return;

			if (ImGui::IsKeyDown(ImGuiKey_W))
				dir = dir + Offsets::Transform::get_forward(relativeTransform);
			if (ImGui::IsKeyDown(ImGuiKey_S))
				dir = dir - Offsets::Transform::get_forward(relativeTransform);
			if (ImGui::IsKeyDown(ImGuiKey_A))
				dir = dir - Offsets::Transform::get_right(relativeTransform);
			if (ImGui::IsKeyDown(ImGuiKey_D))
				dir = dir + Offsets::Transform::get_right(relativeTransform);

			if (ImGui::IsKeyDown(ImGuiKey_LeftShift))
				dir.y -= 1;
			if (ImGui::IsKeyDown(ImGuiKey_Space))
				dir.y += 1;

			Unity::Vector3 prevPos = avatar->getPosition();

			dir = dir * (instance.b_UseAltSpeed && ImGui::IsKeyDown(ImGuiKey_LeftCtrl) ? instance.f_AltSpeed : instance.f_Speed) * (1 / 60.f);

			Unity::Vector3 newPos = prevPos + dir;

			Offsets::Rigidbody::set_Velocity(Offsets::BaseEntity::GetRigidbody(avatar), { 0,0,0 });

			avatar->setPosition(newPos);
		}
	}

	void hook_BaseComponent_LateTickAction(void* this_, float a1) {
		auto& instance = Noclip::Instance();
		if (instance.m_Enabled)
			return;

		Hooks::Call(hook_BaseComponent_LateTickAction, this_, a1);
	}

	void hook_HumanoidMoveFSM_LateTick(void* this_, float a1) {
		auto& instance = Noclip::Instance();
		if (instance.m_Enabled)
			return;

		Hooks::Call(hook_HumanoidMoveFSM_LateTick, this_, a1);
	}
}