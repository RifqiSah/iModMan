#include "hiNative.h"

LPSTR getCurrentDateTime(BOOL withTime) {
	time_t     now = time(0);
	struct tm  tstruct;
	CHAR       buf[80];

	tstruct = *localtime(&now);
	if (withTime)
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	else
		strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	return buf;
}

VOID WINAPI GetLocalPath(LPSTR sPath) {
	CHAR path[MAX_PATH];

	if (!GetCurrentDirectory(sizeof(path), path)) {
		DisplayError((LPSTR)"GetCurrentDirectory");
		return;
	}

	strcpy(sPath, path);
}

VOID WINAPI DisplayError(LPTSTR lpszFunction) {
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

VOID WINAPI DisplayErrorEx(LPSTR sModule, LPTSTR lpszFunction) {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	if (FAILED(StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("\'%s\' failed with error code %d as follows:\n%s"), lpszFunction, dw, lpMsgBuf)))
		printf("FATAL ERROR: Unable to output error code.\n");

	Replace((LPSTR)lpDisplayBuf, '\n', ' ');
	Replace((LPSTR)lpDisplayBuf, '\r\n', ' ');
	WriteLog(sModule, 3, (LPSTR)lpDisplayBuf);
	
	MessageBox(GetActiveWindow(), (LPSTR)lpDisplayBuf, "Error", MB_OK | MB_ICONERROR);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

VOID WINAPI WriteLog(LPSTR sModule, INT iType, LPSTR sMessage) {
	CHAR sFileLog[MAX_PATH];
	// TCHAR sModule[MAX_PATH + 1];
	CHAR type[20];

	GetLocalPath(sFileLog);
	// GetModuleFileName(NULL, sModule, MAX_PATH);
	// PathStripPath(sModule);
	// PathRemoveExtension(sModule);

	strcat(sFileLog, "\\iModMan\\logs\\");
	strcat(sFileLog, sModule);
	strcat(sFileLog, "_");
	strcat(sFileLog, getCurrentDateTime(false));
	strcat(sFileLog, ".log");

	if (iType == 1) strcpy(type, "info");
	else if (iType == 2) strcpy(type, "warning");
	else if (iType == 3) strcpy(type, "error");
	else strcpy(type, "unknnown");

	FILE *fp;
	fp = fopen(sFileLog, "a+");

	// [time] [module] [type] message
	fprintf(fp, "[%s] [%s] [%s] %s\n", getCurrentDateTime(true), sModule, type, sMessage);

	fclose(fp);
}