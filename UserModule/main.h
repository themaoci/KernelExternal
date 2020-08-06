#pragma once
#include <iostream>
#include <windows.h>
#include "Kernelrequests.h"
#include "KernelHelpers.h"
#include <tchar.h>

#include <chrono>
#include <thread>

Kernelrequests* pMem;
int threadDraw = 0;
int readVar1;
int readVar2;

class MainModule {
	/*
		Only things happend in Main program such as console drawing or hotkeys
	*/
public:
	static void createTitle() {
		SetConsoleTitleA(_strdup(random_string(/*you can specify size here*/).c_str()));
	}

	static void RepaintConsole() {
		system("cls");
		MainModule::createConsMenu();
		pMem->GetPidNBaseAddr();
		printf("readVar1: %d\n", readVar1);
		printf("readVar2: %d\n", readVar2);
	}
	static void HotkeysHandling() {
		if (GetAsyncKeyState(VK_F8)) {
			// opens sharedmemory. returns true if it successeded!!
			if (!pMem->OpenSharedMemory()) {
				printf("OpenSharedMemory returned false.[failed]\n");
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else if (GetAsyncKeyState(VK_F6)) {
			MainModule::sendrequests();
			printf("[Completed] sent sendrequests msg to kernel![sendrequests] \n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else if (GetAsyncKeyState(VK_F5)) {
			MainModule::stoploop();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
private:
	static void sendrequests() {

		pMem->ClearMmunloadedDrivers();
		pMem->ClearPIDCache();

		readVar1 = pMem->Read<int>(0x4feec8);
		readVar2 = pMem->Read<int>(0x8a4424);
		//pMem->Write<int>(0x123456,55);
	}

	static void stoploop() {
		auto stopmsg = (char*)MapViewOfFile(hMapFileW, FILE_MAP_WRITE, 0, 0, 4096);

		char stopmms[8];
		strcpy_s(stopmms, "Stop");

		RtlCopyMemory(stopmsg, stopmms, strlen(stopmms) + 1);

		printf("message has been sent to kernel [Stop]! \n");

		FlushViewOfFile(stopmsg, 4096);
		UnmapViewOfFile(stopmsg);
	}
	static std::string random_string(int max = 32)
	{
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(str.begin(), str.end(), generator);
		return str.substr(0, max);
	}
	static void createConsMenu() {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xD); // change color to fushia
		printf(
			"|=======================================|\n"
			"|  Sh-mem driver controll               |\n"
			"| Press F8 to open shared memory.       |\n"
			"| Press F6 to write Memory!.            |\n"
			"| Press F9 to Trigger kernel loop!.     |\n"
			"|=======================================|\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x5); // change color to white
	}
};