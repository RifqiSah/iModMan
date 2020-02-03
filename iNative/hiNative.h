#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <time.h>
#include <Shlwapi.h>
#include <wininet.h>

#pragma warning(disable: 4305)
#pragma warning(disable: 4309)
#pragma warning(disable: 4172)

// Internal and Simple Func
INT Replace(LPSTR str, CHAR ch1, CHAR ch2);
VOID UCase(LPSTR s);
VOID LCase(LPSTR s);

// Exported Func
VOID	WINAPI DisplayError(LPTSTR lpszFunction);
VOID	WINAPI DisplayErrorEx(LPSTR sModule, LPTSTR lpszFunction);
VOID	WINAPI GetLocalPath(LPSTR sPath);
BOOL	WINAPI IsInternetAvailable();
BOOL	WINAPI IsAppAplreadyRunning();
VOID	WINAPI WriteLog(LPSTR sModule, INT iType, LPSTR sMessage);