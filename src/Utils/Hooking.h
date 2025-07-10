#pragma once

#include "../Engine/SDK_utils.h"
#include "detours.h"
#include "Singleton.h"
#include <algorithm>
#include <map>
#include <vector>
#include <Windows.h>
#include <functional>

namespace FN {
	// redefine local Function class here to exclude mutual including
	template<typename TReturn, typename... Args>
	class Function {
	public:
		uintptr_t OS_offset;
		uintptr_t CN_offset;

		TReturn(*Functor)(Args...);

		void operator +=(std::function<TReturn(Args...)> fn) {}

		void Setup() {}
	};
}

class Hooks {
public:
	template<typename TType1, typename TType2>
	static void Attach(TType1 original, TType2 handler) {
		reinterpret_cast<Function<void>&>(original).Setup();

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)reinterpret_cast<Function<void>&>(original).Functor, handler);
		DetourTransactionCommit();
		hooksMap[reinterpret_cast<void*>(handler)] = reinterpret_cast<void*>(reinterpret_cast<Function<void>&>(original).Functor);
	}

	template<typename TType1, typename TType2>
	static void Detach(TType1 original, TType2 handler) {
		reinterpret_cast<Function<void>&>(original).Setup();

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)reinterpret_cast<Function<void>&>(original).Functor, handler);
		DetourTransactionCommit();
		hooksMap.erase(hooksMap.find(reinterpret_cast<void*>(handler)));
	}

	template<typename TType>
	static TType GetOriginal(TType handler) {
		return reinterpret_cast<TType>(hooksMap[reinterpret_cast<void*>(handler)]);
	}

	template<typename TType, typename... Args>
	static TType Call(TType(*handler)(Args...), Args... args) {
		auto org = GetOriginal(handler);
		return org(args...);
	}
private:
	inline static std::map<void*, void*> hooksMap;
};