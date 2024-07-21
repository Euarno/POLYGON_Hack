#pragma once
namespace  Invoke {
    // FastInvoke ʹ�� __fastcall ����Լ��
    template <typename ReturnType, typename... Args>
    inline ReturnType Fast(void* FunctionPtr, Args... args) {
        auto Fn = (ReturnType(__fastcall*)(Args...))(FunctionPtr);
        return Fn(args...);
    }

    // StdInvoke ʹ�� __stdcall ����Լ��
    template <typename ReturnType, typename... Args>
    inline ReturnType Std(void* FunctionPtr, Args... args) {
        auto Fn = (ReturnType(__stdcall*)(Args...))(FunctionPtr);
        return Fn(args...);
    }
}
