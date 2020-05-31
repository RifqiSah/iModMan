#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <initguid.h>
#include <powrprof.h>

#pragma comment(lib, "powrprof.lib")

//
// Gaming Mode (custom)
// {3c0b5af9-4062-4697-ac5d-e3cb614f947b}
//
DEFINE_GUID(GUID_GAMING_MODE, 0x3C0B5AF9, 0x4062, 0x4697, 0xAC, 0x5D, 0xE3, 0xCB, 0x61, 0x4F, 0x94, 0x7B);


VOID SetPowerplan();
VOID RestorePowerplan();
VOID SetPriority();