#include <Windows.h>
#include <map>
#include <iostream>

using namespace std;

#include "..\\iNative\\hiNative.h"
#pragma comment(lib, "..\\lib\\iNative.lib")

BOOL WINAPI ReadPak(LPSTR sSource, LPSTR sMessage);
BOOL WINAPI DiasPackFile(LPSTR sSource, LPSTR sDestination);
VOID WINAPI DiasUnpackFile(LPSTR sSource, LPSTR sDestination);
VOID WINAPI DiasPackBuffer(LPVOID sBuffer, LPSTR sDestination);
VOID WINAPI DiasUnpackBuffer(LPVOID sBuffer, LPSTR sDestination);