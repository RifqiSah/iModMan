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

PCHAR WINAPI substr(PCHAR arr, INT begin, INT len)
{
	PCHAR res = new CHAR[len];
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
	CHAR fName[MAX_PATH];
	INT pos = fullPath - strrchr(fullPath, '\\');

	pos *= -1;
	strcpy(fName, substr(fullPath, pos + 1, strlen(fullPath) - 1));

	return fName;
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