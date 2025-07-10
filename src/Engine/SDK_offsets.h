#pragma once

#include "SDK_types.h"

namespace Offsets {
	namespace Camera {
		REMOTE_FUNC(void, set_fieldOfView, Unity::Camera*, float) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Camera*, get_main) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Vector3, WorldToScreenPoint, Unity::Camera*, Unity::Vector3) { 0x0, 0x0 };
	}
	
	namespace Marshal {
		REMOTE_FUNC(Unity::String*, PtrToStringAnsi, const char*) { 0x0, 0x0 };
	}

	namespace Cursor {
		REMOTE_FUNC(int32_t, get_lockState) { 0x0, 0x0 };
		REMOTE_FUNC(void, set_lockState, int32_t) { 0x0, 0x0 };
		REMOTE_FUNC(bool, get_visible) { 0x0, 0x0 };
		REMOTE_FUNC(void, set_visible, bool) { 0x0, 0x0 };
	}

	namespace Application {
		REMOTE_FUNC(int, get_targetFramerate) { 0x0, 0x0 };
		REMOTE_FUNC(void, set_targetFramerate, int) { 0x0, 0x0 };
	}

	namespace QualitySettings {
		REMOTE_FUNC(void, set_vsyncCount, int) { 0x0, 0x0 };
	}

	namespace Unknown {
		REMOTE_FUNC(void, UnknownPeeking, void*, void*, void*, void*) { 0x0, 0x0 };
	}

	namespace LCAvatarCombat {
		REMOTE_FUNC(float, get_Energy, void*) { 0x0, 0x0 };
		REMOTE_FUNC(bool, IsEnergySkillAvailable, void*) { 0x0, 0x0 };
		REMOTE_FUNC(void, TickSkillCd, void*, float) { 0x0, 0x0 };
	}

	namespace LCAbilityComponent {
		REMOTE_FUNC(void, ReduceModifierDurability, void*, int32_t, float, void*) { 0x0, 0x0 };
	}

	namespace LCBaseCombat {
		REMOTE_FUNC(void, FireBeingHitEvent, void*, uint32_t, void*) { 0x0, 0x0 };
	}

	namespace LCScenePoint {
		REMOTE_FUNC(void, Tick, void*, float) { 0x0, 0x0 };
	}

	namespace MapModule {
		REMOTE_FUNC(void, RequestUnlockTransPoint, void*, void*) { 0x0, 0x0 };
	}

	namespace DataItem {
		REMOTE_FUNC(void, HandleNormalProp, void*, uint32_t, long, void*) { 0x0, 0x0 };
	}

	namespace InLevelPageContext {
		REMOTE_FUNC(void, UpdateView, void*) { 0x0, 0x0 };
	}

	namespace MonoParticleDamageTextContainer {
		REMOTE_FUNC(void, ShowDamegeText, void*, void*, void*) { 0x0, 0x0 };
	}

	namespace GameManager {
		REMOTE_FUNC(void, Update, void*) { 0x0, 0x0 };
	}

	namespace EnviroSky {
		REMOTE_FUNC(void*, get_Instance) { 0x0, 0x0 };
		REMOTE_FUNC(void, ChangeWeather, void*, void*, float, float, bool) { 0x0, 0x0 };
	}

	namespace PostProcessLayer {
		REMOTE_FUNC(void, Update, void*) { 0x0, 0x0 };
		namespace Offsets {
			inline static int outlineCorrectionWidth = 0x0;
			inline static int _gammaValue = 0x0;
			inline static int m_InnerResolutionScale = 0x0;
			inline static int cameraBufferDirty = 0x0;
			inline static int _gammaValueChanged = 0x0;
		}
	}

	namespace VCMonsterAIController {
		REMOTE_FUNC(void, TryDoSkill, void*, uint32_t) { 0x0, 0x0 };
	}

	namespace LCSelectPickup {
		REMOTE_FUNC(bool, IsInPosition, void*, void*) { 0x0, 0x0 };
		REMOTE_FUNC(bool, IsOutPosition, void*, void*) { 0x0, 0x0 };
		REMOTE_FUNC(void, AddInteeBtnById, void*, MoleMole::BaseEntity*) { 0x0, 0x0 };
	}

	namespace HumanoidMoveFSM {
		REMOTE_FUNC(void, LateTick, void*, float) { 0x0, 0x0 };

		REMOTE_FUNC(void, UpdateSprintCooldown, void*, float) { 0x0, 0x0 };
	}

	namespace SingletonManager {
		REMOTE_FUNC(void*, get_Instance) { 0x0, 0x0 };
		REMOTE_FUNC(void*, GetSingletonInstance, void*, Unity::String*) { 0x0, 0x0 };
	}

	namespace PlayerModule {
		REMOTE_FUNC(void, HandleAvatarAppear2, void*, MoleMole::SceneEntityInfo*, void*, uint32_t) { 0x0, 0x0 };
	}

	namespace VCHumanoidMove {
		REMOTE_FUNC(void, NotifyLandVelocity, void*, Unity::Vector3, float) { 0x0, 0x0 };
	}

	namespace Transform {
		REMOTE_FUNC(Unity::Vector3, get_localPosition, Unity::Transform*) { 0x0, 0x0 };
		REMOTE_FUNC(void, set_localPosition, Unity::Transform*, Unity::Vector3) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Vector3, get_forward, Unity::Transform*) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Vector3, get_right, Unity::Transform*) { 0x0, 0x0 };

		REMOTE_FUNC(void*, get_parent, void*) { 0x0, 0x0 };
	}

	namespace Object {
		REMOTE_FUNC(Unity::String*, get_name, void*) { 0x0, 0x0 };
	}

	namespace Component {
		REMOTE_FUNC(Unity::Transform*, get_transform, void*) { 0x0, 0x0 };
		REMOTE_FUNC(void*, get_gameObject, void*) { 0x0, 0x0 };
	}

	namespace Rigidbody {
		REMOTE_FUNC(void, set_detectCollisions, void*, bool) { 0x0, 0x0 };
	}

	namespace InLevelCutScenePageContext {
		REMOTE_FUNC(void, UpdateView, void*) { 0x0, 0x0 };
	}

	namespace MonoTypeWriter {
		REMOTE_FUNC(void, Update, void*) { 0x0, 0x0 };
	}

	namespace MonoReusableList {
		REMOTE_FUNC(void*, get_item, void*, int) { 0x0, 0x0 };
	}

	namespace MonoSelectItem {
		REMOTE_FUNC(void, OnSelectItem, void*) { 0x0, 0x0 };
	}

	namespace Action {
		REMOTE_FUNC(void, Invoke, void*) { 0x0, 0x0 };
	}

	namespace EntityManager {
		REMOTE_FUNC(Unity::monoList<MoleMole::BaseEntity*>*, GetEntities, MoleMole::EntityManager*) {0x0, 0x0};

		REMOTE_FUNC(MoleMole::BaseEntity*, GetLocalAvatarEntity, MoleMole::EntityManager*) { 0x0, 0x0 };
		REMOTE_FUNC(MoleMole::BaseEntity*, GetValidEntity, MoleMole::EntityManager*, uint32_t) { 0x0, 0x0 };
	}

	namespace BaseEntity {
		REMOTE_FUNC(MoleMole::EntityType, get_EntityType, MoleMole::BaseEntity*) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::GameObject*, get_GameObject, MoleMole::BaseEntity*) { 0x0, 0x0 };
		REMOTE_FUNC(uint32_t, get_runtimeId, MoleMole::BaseEntity*) { 0x0, 0x0 };
	
		REMOTE_FUNC(Unity::Vector3, get_Position, MoleMole::BaseEntity*) { 0x0, 0x0 };
		REMOTE_FUNC(void, set_Position, MoleMole::BaseEntity*, Unity::Vector3, bool) { 0x0, 0x0 };

		REMOTE_FUNC(void*, GetRigidbody, MoleMole::BaseEntity*) { 0x0, 0x0 };
		REMOTE_FUNC(void*, GetAnimator, MoleMole::BaseEntity*) { 0x0, 0x0 };

		REMOTE_FUNC(Unity::String*, get_name, MoleMole::BaseEntity*) { 0x0, 0x0 };
	}

	namespace Animator {
		REMOTE_FUNC(void, set_Speed, void*, float) { 0x0, 0x0 };
	}

	namespace Rigidbody {
		REMOTE_FUNC(void, set_Velocity, void*, Unity::Vector3) { 0x0, 0x0 };
	}

	namespace GameObject {
		REMOTE_FUNC(Unity::Transform*, get_transform, Unity::GameObject*) { 0x0, 0x0 };
		REMOTE_FUNC(void*, GetComponent, Unity::GameObject*, Unity::String*) { 0x0, 0x0 };
	}

	namespace StageManager {
		REMOTE_FUNC(Unity::Bounds, GetBounds, Unity::GameObject*) { 0x0, 0x0 };
	}

	namespace Screen {
		REMOTE_FUNC(int, get_height) { 0x0, 0x0 };
	}

	namespace ItemModule {
		REMOTE_FUNC(void, PickItem, void*, uint32_t) { 0x0, 0x0 };
	}

	namespace LoadingManager {
		REMOTE_FUNC(bool, IsLoaded, MoleMole::LoadingManager*) { 0x0, 0x0 };
	}

	namespace VCAnimatorMove {
		REMOTE_FUNC(void, LateTick, void*, float) { 0x0, 0x0 };
		REMOTE_FUNC(void, DrownWater, void*) { 0x0, 0x0 };
	}

	namespace WandererFlightHandler {
		REMOTE_FUNC(void, Tick, void*, float) { 0x0, 0x0 };
		REMOTE_FUNC(void, SetValue, void*, float) { 0x0, 0x0 };
	}

	namespace LevelSyncCombatPlugin {
		REMOTE_FUNC(void, RequestSceneEntityMoveReq, void*, uint32_t, void*, bool, uint32_t, uint32_t) { 0x0, 0x0 };
	}

	namespace ActorAbilityPlugin {
		REMOTE_FUNC(float, GetValueFromKey, void*, Unity::String*) { 0x0, 0x0 };
		REMOTE_FUNC(bool, SetDynamicFloat, void*, Unity::String*, float, bool) { 0x0, 0x0 };
	}

	namespace VCBaseMove {
		REMOTE_FUNC(bool, CanWalkOnWater, void*) { 0x0, 0x0 };
	}
	
	namespace MonoMapMark {
		REMOTE_FUNC(void, Update, void*) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Vector2, get_levelMapPos, void*) { 0x0, 0x0 };
		REMOTE_FUNC(float, get_height, void*) { 0x0, 0x0 };
	};

	namespace InLevelMapPageContext {
		REMOTE_FUNC(void, OnMapClicked, void*, Unity::Vector2) { 0x0, 0x0 };
		REMOTE_FUNC(void, OnMarkClicked, void*, void*) { 0x0, 0x0 };
	}

	namespace MonoInLevelMapPage {
		REMOTE_FUNC(MoleMole::Rect, get_mapRect, void*) { 0x0, 0x0 };
		REMOTE_FUNC(void*, get_mapBackground, void*) { 0x0, 0x0 };
	}

	namespace BasePageContext {
		REMOTE_FUNC(void, ClosePage, void*) { 0x0, 0x0 };
	}

	namespace RectTransformUtility {
		REMOTE_FUNC(bool, ScreenPointToLocalPointInRectangle, void*, Unity::Vector2, void*, Unity::Vector2*) { 0x0, 0x0 };
	}

	namespace Miscs {
		REMOTE_FUNC(float, CalcCurrentGroundHeight, float, float) { 0x0, 0x0 };
		REMOTE_FUNC(Unity::Vector3, GenWorldPos, Unity::Vector2) { 0x0, 0x0 };
	}

	namespace WorldShiftManager {
		REMOTE_FUNC(Unity::Vector3, GetRelativePosition, Unity::Vector3) { 0x0, 0x0 };
	}

	namespace LevelTimeManager {
		REMOTE_FUNC(void, SetInternalTimeOfDay, void*, float, bool, bool, bool) { 0x0, 0x0 };
	}
}