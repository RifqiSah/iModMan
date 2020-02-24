#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <Shlwapi.h>

using namespace std;

#include "..\\iNative\\hiNative.h"
#pragma comment(lib, "..\\lib\\iNative.lib")

#include "zlib/zlib.h"
#pragma comment(lib, "..\\lib\\zlibwapi.lib")

// Eris
BOOL WINAPI ReadEris(LPSTR sSource, LPSTR sMessage);

// DN
BOOL WINAPI DnPakRead(LPSTR sSource, LPSTR sMessage);
BOOL WINAPI DnPakPack(LPSTR sSource, LPSTR sDestination);
BOOL WINAPI DnPakUnpack(LPSTR sSource, LPSTR sDestination);

// Dias
BOOL WINAPI DiasPakRead(LPSTR sSource, LPSTR sMessage);
BOOL WINAPI DiasPakPack(LPSTR sSource, LPSTR sDestination);
BOOL WINAPI DiasPakUnpack(LPSTR sSource, LPSTR sDestination);
