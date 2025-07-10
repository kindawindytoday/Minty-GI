#include "SDK.h"

namespace Unity
{
	String* String::FromCString(std::string text) 
	{
		return Offsets::Marshal::PtrToStringAnsi(text.c_str());
	}

	std::string String::ToCString() 
	{
		if (this == nullptr) return ("<NULL>");

		std::u16string u16(reinterpret_cast<const char16_t*>(reinterpret_cast<MonoArray*>(this)->chars));
		return std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}.to_bytes(u16);
	}

	Transform* GameObject::GetTransform() 
	{
		if (this == nullptr) return 0;
		return Offsets::GameObject::get_transform(this);
	}

	void Transform::setPosition(Unity::Vector3 pos) 
	{
		if (this == nullptr) return;
		Offsets::Transform::set_localPosition(this, pos);
	}

	Unity::Vector3 Transform::getPosition() 
	{
		if (this == nullptr) return {0,0,0};
		return Offsets::Transform::get_localPosition(this);
	}
}

namespace MoleMole 
{
	EntityManager* EntityManager::get_EntityManager() 
	{
		try {
			auto mgr = Offsets::SingletonManager::get_Instance();
			if (mgr != nullptr) {
				auto loadingMgr = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString("<...>")); // Class name of EntityManager
				if (loadingMgr != nullptr) return (EntityManager*)loadingMgr;
			}
			return 0;
		}
		catch (...) {
			return 0;
		}
	}

	std::vector<BaseEntity*> EntityManager::entities() {
		std::vector<BaseEntity*> vector;

		if (this == nullptr) return vector;

		auto list = Offsets::EntityManager::GetEntities(this);
		if (list == nullptr) return vector;

		for (int i = 0; i < list->size; i++) {
			auto ent = list->items->operator[](i);
			if (ent == nullptr) continue;
			vector.push_back(ent);
		}

		return vector;
	}

	BaseEntity* EntityManager::avatar() 
	{
		if (this == nullptr) return 0;
		try {
			return Offsets::EntityManager::GetLocalAvatarEntity(this);
		}
		catch (...) {
			return 0;
		}
	}

	EntityType BaseEntity::type() 
	{
		if (this == nullptr) return EntityType::None;
		try {
			return Offsets::BaseEntity::get_EntityType(this);
		}
		catch (...) {
			return EntityType::None;
		}
	}

	uint32_t BaseEntity::runtimeId() 
	{
		if (this == nullptr) return 0;
		try {
			return Offsets::BaseEntity::get_runtimeId(this);
		}
		catch (...) {
			return 0;
		}
	}

	Unity::GameObject* BaseEntity::get_GameObject() 
	{
		if (this == nullptr) return 0;
		return Offsets::BaseEntity::get_GameObject(this);
	}

	void BaseEntity::setPosition(Unity::Vector3 pos) 
	{
		if (this == nullptr) return;
		Offsets::BaseEntity::set_Position(this, pos, true);
	}

	Unity::Vector3 BaseEntity::getPosition() 
	{
		if (this == nullptr) return {0,0,0};
		return Offsets::BaseEntity::get_Position(this);
	}

	void* BaseEntity::animator() 
	{
		if (this == nullptr) return 0;
		return Offsets::BaseEntity::GetAnimator(this);
	}

	std::string BaseEntity::name() 
	{
		if (this == nullptr) return ("<NULL>");
		return Offsets::BaseEntity::get_name(this)->ToCString();
	}

	LoadingManager* LoadingManager::get_LoadingManager() 
	{
		auto mgr = Offsets::SingletonManager::get_Instance();
		if (mgr != nullptr) {
			auto loadingMgr = Offsets::SingletonManager::GetSingletonInstance(mgr, Unity::String::FromCString("<...>")); // Classname of LoadingManager
			if (loadingMgr != nullptr) return (LoadingManager*)loadingMgr;
		}
		return 0;
	}

	bool LoadingManager::IsLoaded() 
	{
		if (this == nullptr) return 0;
		return Offsets::LoadingManager::IsLoaded(this);
	}
}