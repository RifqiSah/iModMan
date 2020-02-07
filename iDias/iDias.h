#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <Shlwapi.h>

using namespace std;

#include "..\\iNative\\hiNative.h"
#pragma comment(lib, "..\\lib\\iNative.lib")

BOOL WINAPI ReadPak(LPSTR sSource, LPSTR sMessage);
BOOL WINAPI DiasPackFile(LPSTR sSource, LPSTR sDestination);
BOOL WINAPI DiasUnpackFile(LPSTR sSource, LPSTR sDestination);
BOOL WINAPI DiasPackBuffer(LPVOID sBuffer, LPSTR sDestination);
BOOL WINAPI DiasUnpackBuffer(LPVOID sBuffer, LPSTR sDestination);