#pragma once

#include <windows.h>
#include <iostream>
#include <string>

// for debugging shit - franco dont know he can use that in post processor ...
// #define DBG_PRINT


ULONG PID;
ULONG64 baseaddr = NULL;
HANDLE hMapFileW;
HANDLE hMapFileR;
HANDLE g_hMutex;

HANDLE SharedEvent_dataarv;
HANDLE SharedEvent_trigger;
HANDLE SharedEvent_ready2read;

const std::string applicationName = "notepad.exe";
LPCSTR globDataArrived = "Global\\DataArrived";
LPCSTR globTrigger = "Global\\trigger";
LPCSTR globReadyRead = "Global\\ReadyRead";
LPCSTR globSharedMem = "Global\\SharedMem";