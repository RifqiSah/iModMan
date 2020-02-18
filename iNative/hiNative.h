#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <string>
#include <time.h>
#include <Shlwapi.h>
#include <wininet.h>
#include <PathCch.h>

#pragma warning(disable: 4305)
#pragma warning(disable: 4309)
#pragma warning(disable: 4172)

// Internal and Simple Func
LPSTR	WINAPI getCurrentDateTime(BOOL withTime);
PCHAR	WINAPI substr(PCHAR arr, INT begin, INT len);
INT		WINAPI strreplace(LPSTR str, CHAR ch1, CHAR ch2);
VOID	WINAPI strucase(LPSTR s);
VOID	WINAPI strlcase(LPSTR s);
LPSTR	WINAPI ExtractFileName(LPSTR fullPath);
VOID	WINAPI CreateDirectoryAndSub(LPSTR path);
LPSTR	WINAPI RemoveFilename(LPSTR myStr);
BOOL	WINAPI DirectoryExists(LPSTR szPath);

// Exported Func
VOID	WINAPI DisplayError(LPTSTR lpszFunction);
VOID	WINAPI DisplayErrorEx(LPSTR sModule, LPTSTR lpszFunction);
VOID	WINAPI GetLocalPath(LPSTR sPath);
BOOL	WINAPI IsInternetAvailable();
BOOL	WINAPI IsAppAplreadyRunning();
VOID	WINAPI WriteLog(LPSTR sModule, INT iType, LPSTR sMessage);