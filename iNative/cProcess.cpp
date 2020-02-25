#include "hiNative.h"

BOOL WINAPI IsAppAplreadyRunning() {
	BOOL ret = FALSE;
	HANDLE hMutex = CreateMutex(NULL, TRUE, "iModMan_Mutex");
	if (!hMutex) {
		DisplayErrorEx("iNative:IsAppAplreadyRunning", "CreateMutex");
	}

	switch (::GetLastError()) {
	case ERROR_SUCCESS:
		ret = FALSE;
		break;

	case ERROR_ALREADY_EXISTS:
		ret = TRUE;
		break;

	default:
		ret = TRUE;
		break;
	}

	return ret;
}