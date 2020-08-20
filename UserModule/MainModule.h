#pragma once
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <chrono>
#include <thread>

#include "xor_str.h"
#include "Kernelrequests.h"
#include "KernelHelpers.h"

std::string errorList;
int readVar1 = 0;
int readVar2 = 0;
bool memonyOpen = false;

class MainModule {
	/*
		Only things happend in Main program such as console drawing or hotkeys
	*/

private:
	void cls()
	{
		// Get the Win32 handle representing standard output.
		// This generally only has to be done once, so we make it static.
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD topLeft = { 0, 0 };

		// std::cout uses a buffer to batch writes to the underlying console.
		// We need to flush that to the console because we're circumventing
		// std::cout entirely; after we clear the console, we don't want
		// stale buffered text to randomly be written out.
		std::cout.flush();

		// Figure out the current width and height of the console window
		if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
			// TODO: Handle failure!
			abort();
		}
		DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

		DWORD written;

		// Flood-fill the console with spaces to clear it
		FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

		// Reset the attributes of every character to the default.
		// This clears all background colour formatting, if any.
		FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

		// Move the cursor back to the top left for the next sequence of writes
		SetConsoleCursorPosition(hOut, topLeft);
	}
	void print(const char* text) {
		errorList.append(text).append("\n");
	}
	void sendrequests() {

		pMem->ClearMmunloadedDrivers();
		pMem->ClearPIDCache();

		readVar1 = pMem->Read<int>((UINT_PTR)0x4feec8);
		readVar2 = pMem->Read<int>((UINT_PTR)0x8a4424);
		//pMem->Write<int>(0x123456,55);
	}

	void stoploop() {
		auto stopmsg = (char*)MapViewOfFile(hMapFileW, FILE_MAP_WRITE, 0, 0, 4096);

		char stopmms[8];
		strcpy_s(stopmms, "Stop");

		RtlCopyMemory(stopmsg, stopmms, strlen(stopmms) + 1);

		print("message has been sent to kernel [Stop]!");

		FlushViewOfFile(stopmsg, 4096);
		UnmapViewOfFile(stopmsg);
	}
	std::string random_string(int max = 32)
	{
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
		std::random_device rd;
		std::mt19937 generator(rd());
		std::shuffle(str.begin(), str.end(), generator);
		return str.substr(0, max);
	}
	void createConsMenu() {
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xD); // change color to fushia
		//std::wcout << L"╔═══════════════════════════════════╗\n" << L"║ Press F8 to open shared memory.   ║\n" << L"║ Press F6 to write Memory!.        ║\n" << L"║ Press F9 to Trigger kernel loop!. ║\n" << L"╚═══════════════════════════════════╝\n";
		printf("%ls",L"╔═══════════════════════════════════╗\n"
			L"║ Press F8 to open shared memory.   ║\n"
			L"║ Press F6 to write Memory!.        ║\n"
			L"║ Press F9 to Trigger kernel loop!. ║\n"
			L"╚═══════════════════════════════════╝\n");
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x5); // change color to white
	}
public:
	Kernelrequests* pMem;

	void drawErrorText() {

	}
	void ClearErrorLog() {
		std::size_t found = errorList.find("\n");
		if (found != std::string::npos)
			errorList.erase(0, found + 1);
	}
	void createTitle() {
		SetConsoleTitleA(_strdup(random_string(/*you can specify size here*/).c_str()));
	}

	void RepaintConsole() {
		cls();
		std::wcout << L"...";

		createConsMenu();
		pMem->GetPidNBaseAddr();
		//printf("readVar1: %d\n", readVar1);
		//printf("readVar2: %d\n", readVar2);
		printf(errorList.c_str());
		//MainModule::drawErrorText();
	}
	void HotkeysHandling() {
		if (GetAsyncKeyState(VK_F8)) {
			// opens sharedmemory. returns true if it successeded!!
			if (!pMem->OpenSharedMemory()) {
				errorList.append("OpenSharedMemory returned false.[failed]\n");
			}
			else memonyOpen = true;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else if (GetAsyncKeyState(VK_F6) && memonyOpen) {
			sendrequests();
			errorList.append("[Completed] sent sendrequests msg to kernel![sendrequests]\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xA);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else if (GetAsyncKeyState(VK_F5)) {
			stoploop();
			errorList.append("Stopping Loop\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}

};