#include <Windows.h>
#include "hMain.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		WriteLog("iCrpto:DllMain", 1, "Init ModMan Cryptographic Library");
		break;

	case DLL_PROCESS_DETACH:
		WriteLog("iCrpto:DllMain", 1, "Module unloaded");
		break;
	}

	return TRUE;
}