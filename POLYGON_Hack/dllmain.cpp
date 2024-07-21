#include <Windows.h>
#include <GlobalContext/GlobalContext.h>


BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        GlobalContext::getInstance().Initialize();
    }
    return TRUE;
}

