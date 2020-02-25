#include <Windows.h>
#include "iDias.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		WriteLog("iDias:DllMain", 1, "Init ModMan Dias Packer Support Library");
		break;

	case DLL_PROCESS_DETACH:
		WriteLog("iDias:DllMain", 1, "Module unloaded");
		break;
	}

	return TRUE;
}