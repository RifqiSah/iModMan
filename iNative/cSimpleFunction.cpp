#include "hiNative.h"

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