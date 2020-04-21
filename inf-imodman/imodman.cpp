#include <Windows.h>

VOID getDllPath(LPSTR sPath) {
	CHAR path[MAX_PATH];

	if (!GetCurrentDirectoryA(sizeof(path), path)) {
		return;
	}

	strcpy(sPath, path);
}

VOID ModuleInit(PVOID athena) {
	CHAR buff[MAX_PATH];
	DWORD pId;
	HANDLE hProc;

	pId = GetCurrentProcessId();
	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);

	wsprintf(buff, "Dragonnest PID is %i", pId);
	MessageBoxA(NULL, buff, "Informate", MB_ICONINFORMATION);

	ReadProcessMemory(hProc, (PBYTE*)0x6727d43c, &buff, sizeof(buff), 0);
	Sleep(5000);
	MessageBoxA(NULL, buff, "Informate", MB_ICONINFORMATION);

	// Terminta process!
	CloseHandle(hProc);
	TerminateProcess(GetCurrentProcess(), 0);
}