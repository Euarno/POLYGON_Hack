#pragma once
namespace  Invoke {
    // FastInvoke 使用 __fastcall 调用约定
    template <typename ReturnType, typename... Args>
    inline ReturnType Fast(void* FunctionPtr, Args... args) {
        auto Fn = (ReturnType(__fastcall*)(Args...))(FunctionPtr);
        return Fn(args...);
    }

    // StdInvoke 使用 __stdcall 调用约定
    template <typename ReturnType, typename... Args>
    inline ReturnType Std(void* FunctionPtr, Args... args) {
        auto Fn = (ReturnType(__stdcall*)(Args...))(FunctionPtr);
        return Fn(args...);
    }
}
