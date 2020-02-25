#include "hiNative.h"

VOID WINAPI GetLocalPath(LPSTR sPath) {
	CHAR path[MAX_PATH];

	if (!GetCurrentDirectory(sizeof(path), path)) {
		DisplayError("GetCurrentDirectory");
		return;
	}

	strcpy(sPath, path);
}

VOID WINAPI DisplayError(LPCSTR lpszFunction) {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

	if (FAILED(StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("\'%s\' failed with error code %d as follows:\n%s"), lpszFunction, dw, lpMsgBuf)))
		printf("FATAL ERROR: Unable to output error code.\n");

	MessageBox(GetActiveWindow(), (LPSTR)lpDisplayBuf, "Error", MB_OK | MB_ICONERROR);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

VOID WINAPI DisplayErrorEx(LPCSTR sModule, LPCSTR lpszFunction) {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	if (FAILED(StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("\'%s\' failed with error code %d as follows:\n%s"), lpszFunction, dw, lpMsgBuf)))
		printf("FATAL ERROR: Unable to output error code.\n");

	strreplace((LPSTR)lpDisplayBuf, '\n', ' ');
	strreplace((LPSTR)lpDisplayBuf, '\r\n', ' ');
	WriteLog(sModule, 3, (LPSTR)lpDisplayBuf);
	
	MessageBox(GetActiveWindow(), (LPSTR)lpDisplayBuf, "Error", MB_OK | MB_ICONERROR);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

/* 1. info | 2. warning | 3.error | 4. trace | 5. debug */
VOID WINAPI WriteLog(LPCSTR sModule, INT iType, LPCSTR sMessage, ...) {
	CHAR sFileLog[MAX_PATH];
	// TCHAR sModule[MAX_PATH + 1];
	CHAR type[20];

	GetLocalPath(sFileLog);
	// GetModuleFileName(NULL, sModule, MAX_PATH);
	// PathStripPath(sModule);
	// PathRemoveExtension(sModule);

	strcat(sFileLog, "\\iModMan\\logs\\");
	strcat(sFileLog, substr((LPSTR)sModule, 0, (INT)(strchr(sModule, ':') - sModule)));
	strcat(sFileLog, "_");
	strcat(sFileLog, getCurrentDateTime(false));
	strcat(sFileLog, ".log");

	if (iType == 1) strcpy(type, "info");
	else if (iType == 2) strcpy(type, "warning");
	else if (iType == 3) strcpy(type, "error");
	else if (iType == 4) strcpy(type, "trace");
	else if (iType == 5) strcpy(type, "debug");
	else strcpy(type, "unknown");

	// Parsing parameter
	va_list argptr;
	va_start(argptr, sMessage);

	LPSTR Message = (LPSTR)malloc(MSG_MAX + 1);

	if (_vsnprintf(Message, MSG_MAX, sMessage, argptr) == -1)
		return;
	// End parsing param

	FILE *fp;
	fp = fopen(sFileLog, "a+");
	// [time] [module] [type] message
	fprintf(fp, "[%s] [%s] [%s] %s\n", getCurrentDateTime(true), sModule, type, Message);
	fclose(fp);

	free(Message);
	va_end(argptr);
}