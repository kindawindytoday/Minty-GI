#pragma once

#include <Windows.h>   // uintptr_t, GetModuleHandle
#include <functional>  // std::function

enum BaseType {
    UserAssembly,
    UnityPlayer
};

static uintptr_t BaseAddressGA = 0;
static uintptr_t BaseAddressUP = 0;

template<typename FuncType>
class Function;

template<typename Return, typename... Args>
class Function<std::function<Return(Args...)>> {
public:
    uintptr_t OS_offset;                                 // OSRel offset (Global)
    uintptr_t CN_offset;                                 // CNRel offset (China)
    BaseType Type;                                       // Is it in UserAssembly or UnityPlayer
    
    std::function<Return(Args...)> Functor;              // Internal object, representating a pointer to the target function ingame

    void Setup(std::function<Return(Args...)> param) {   // Needs to be called once before Invoking/Hooking
        while (BaseAddressGA == 0 || BaseAddressUP == 0) {
            BaseAddressUA = (uintptr_t)GetModuleHandleA("UserAssembly.dll");
            BaseAddressUP = (uintptr_t)GetModuleHandleA(OBF("UnityPlayer.dll");
        }

        //const auto& version = GameVersion::GetOrLoad();

        Base = Type == GameAssembly ? BaseAddressGA : BaseAddressUP;
        //Functor = (TReturn(*)(Args...)) ((Type == GameAssembly ? BaseAddressGA : BaseAddressUP) +
            //(version == Version::GLOBAL ? OS_offset : CN_offset));
        Functor = (Func)((Type == GameAssembly ? BaseAddressGA : BaseAddressUP) + (OS_offset));
    }

    Return operator()(Args... args) {                    // () operator, so object can be invoked, like:   my_func(4, 2);
        if (!Functor) {
            Setup()
        }
        return Functor(args...);
    }

    Function(uintptr_t os, uintptr_t cn, BaseType type = GameAssembly) : OS_offset(os), CN_offset(cn), Type(type) {}
};

template<typename T>
class Field {
public:
    int OS_offset;                                 // OSRel offset (Global)
    int CN_offset;                                 // CNRel offset (China)
};

#define DO_METHOD(Return, Name, ...) \
inline static Function<std::function<Return(__VA_ARGS__)>> Name

#define DO_FIELD(Return, Name) \
inline static Field<Return> Name

#define SDK_FIELDS_GET_SET() \
    template<typename T> \
    void set_field(Field<T> field, T value) { \
        *reinterpret_cast<T*>( (uintptr_t)this + field.OS_offset ) = value; \
    } \
\
    template<typename T> \
    T get_field(Field<T> field) { \
        return *reinterpret_cast<T*>( (uintptr_t)this + field.OS_offset ); \
    }