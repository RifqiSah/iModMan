#include <Windows.h>
#include "hiNative.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		WriteLog("iNative:DllMain", 1, "Init ModMan Native API Library");
		break;

	case DLL_PROCESS_DETACH:
		WriteLog("iNative:DllMain", 1, "Module unloaded");
		break;
	}

	return TRUE;
}