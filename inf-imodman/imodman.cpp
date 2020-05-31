#include "imodman.h"

VOID getDllPath(LPSTR sPath) {
	CHAR path[MAX_PATH];

	if (!GetCurrentDirectoryA(sizeof(path), path)) {
		return;
	}

	strcpy(sPath, path);
}

VOID ReadDNMemory() {
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

VOID TerminateAthena() {
	DWORD parentPid = -1;
	ULONG_PTR pbi[6];
	ULONG ulSize = 0;
	LONG(WINAPI * NtQueryInformationProcess)(HANDLE ProcessHandle, ULONG ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);
	*(FARPROC*)&NtQueryInformationProcess = GetProcAddress(LoadLibraryA("ntdll.dll"), "NtQueryInformationProcess");
	
	if (NtQueryInformationProcess) {
		if (NtQueryInformationProcess(GetCurrentProcess(), 0, &pbi, sizeof(pbi), &ulSize) >= 0 && ulSize == sizeof(pbi))
			parentPid = (DWORD)pbi[5];
	}
	
	if (parentPid != -1) {
		TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, parentPid), 0);
	}
}

VOID SetPowerplan() {
	PowerSetActiveScheme(0, &GUID_GAMING_MODE);
}

VOID RestorePowerplan() {
	PowerSetActiveScheme(0, &GUID_TYPICAL_POWER_SAVINGS);
}

VOID SetPriority() {
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
}

VOID ModuleInit(PVOID athena) {
	SetPriority();
	TerminateAthena();
}