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

PCHAR substr(PCHAR arr, INT begin, INT len)
{
	PCHAR res = new CHAR[len];
	for (INT i = 0; i < len; i++)
		res[i] = *(arr + begin + i);

	res[len] = 0;
	return res;
}

INT Replace(LPSTR str, CHAR ch1, CHAR ch2)
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

VOID UCase(LPSTR s)
{
	LPSTR p;

	for (p = s; *p != '\0'; p++)
		*p = (CHAR)toupper(*p);

}

VOID LCase(LPSTR s)
{
	LPSTR p;

	for (p = s; *p != '\0'; p++)
		*p = (CHAR)tolower(*p);
}