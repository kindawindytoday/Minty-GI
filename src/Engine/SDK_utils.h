#pragma once

#include <Windows.h>
#include "../Utils/Singleton.h"
#include <functional>
#include <vector>

#pragma warning( disable : 4789 )

inline static uintptr_t BaseAddress = 0;

template<typename TReturn, typename... Args>
class Function 
{
public:
    uintptr_t OS_offset;
    uintptr_t CN_offset;

    TReturn(*Functor)(Args...) = nullptr;

    void Setup() 
    {
        while (BaseAddress == 0) {
            BaseAddress = (uintptr_t)GetModuleHandleA(0);
        }

        // This should have a game build check which would decide offset to use: OS or CN
        Functor = (TReturn(*)(Args...))(BaseAddress + OS_offset);
    }

    TReturn operator()(Args... args) 
    {
        if ((uintptr_t)Functor > BaseAddress) {
            return Functor(args...);
        }
        else {
            Setup();
            return Functor(args...);
        }
    }

    Function(uintptr_t os, uintptr_t cn) : OS_offset(os), CN_offset(cn) {}
};

#define REMOTE_FUNC(ret, name, ...) inline static Function<ret, __VA_ARGS__> name
