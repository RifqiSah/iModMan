#include "hiNative.h"

BOOL WINAPI IsInternetAvailable()
{
	return InternetCheckConnection("https://www.alriftech.com/api/v2", FLAG_ICC_FORCE_CONNECTION, 0);
}