#include "hiNative.h"

LPSTR WINAPI getCurrentDateTime(BOOL withTime) {
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

LPSTR WINAPI substr(LPSTR arr, INT begin, INT len)
{
	LPSTR res = new CHAR[len];
	for (INT i = 0; i < len; i++)
		res[i] = *(arr + begin + i);

	res[len] = 0;
	return res;
}

INT WINAPI strreplace(LPSTR str, CHAR ch1, CHAR ch2)
{
	INT changes = 0;
	while (*str)
	{
		if (*str == ch1)
		{
			*str = ch2;
			changes++;
		}
		str++;
	}

	return changes;
}

VOID WINAPI strucase(LPSTR s)
{
	LPSTR p;

	for (p = s; *p != '\0'; p++)
		*p = (CHAR)toupper(*p);

}

VOID WINAPI strlcase(LPSTR s)
{
	LPSTR p;

	for (p = s; *p != '\0'; p++)
		*p = (CHAR)tolower(*p);
}

LPSTR WINAPI ExtractFileName(LPSTR fullPath)
{
	CHAR path[MAX_PATH];

	strcpy(path, fullPath);
	strcpy(path, PathFindFileName(fullPath));

	if (strcmp(PathFindExtension(path), ".pak") == 0 || strcmp(PathFindExtension(path), ".PAK") == 0)
		PathRemoveExtension(path);

	return path;
}

VOID WINAPI CreateDirectoryAndSub(LPSTR path) {
	CHAR folder[MAX_PATH];
	PCHAR end;

	ZeroMemory(folder, MAX_PATH * sizeof(CHAR));
	end = strchr(path, L'\\');

	while (end != NULL) {
		strncpy(folder, path, end - path + 1);
		if (!CreateDirectory(folder, NULL)) {
			DWORD err = GetLastError();

			if (err != ERROR_ALREADY_EXISTS)
			{
				// do whatever handling you'd like
			}
		}

		end = strchr(++end, L'\\');
	}
}

LPSTR WINAPI RemoveFilename(LPSTR myStr) {
	LPSTR retStr;
	LPSTR lastExt;

	if (myStr == NULL)
		return NULL;

	if ((retStr = (PCHAR)malloc(strlen(myStr) + 1)) == NULL)
		return NULL;

	strcpy(retStr, myStr);
	lastExt = strrchr(retStr, '\\');
	if (lastExt != NULL)
		*lastExt = '\0';

	return retStr;
}

BOOL WINAPI DirectoryExists(LPSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}