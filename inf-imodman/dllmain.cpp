#include "imodman.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            SetPowerplan();
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;

        case DLL_PROCESS_DETACH:
            RestorePowerplan();
            break;
    }

    return TRUE;
}

