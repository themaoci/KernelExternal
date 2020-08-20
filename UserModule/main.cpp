#include <iostream>
#include <windows.h>
#include "Kernelrequests.h"
#include "KernelHelpers.h"
#include "main.h"
#include "MainModule.h"
#include <tchar.h>

#include <chrono>
#include <thread>

void ConsoleLoop() {
	while (true) {
		mModule->RepaintConsole();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));// wait 100ms
		// we are not closing this loop cause its main thread one used in separate thread for performance
	}
}
void HotkeyLoop() {
	while (true) {
		mModule->HotkeysHandling();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main() {
	// WARM UP
	mModule->createTitle();
	// create security descriptor.
	mModule->pMem->createSecuritydesc();
	// creates events 
	mModule->pMem->CreateSharedEvents();
	//Starting threads
	std::thread thread_01(&ConsoleLoop);
	std::thread thread_02(&HotkeyLoop);
	// add threads for esp drawings also for updating variables best will be to use 2/3 separate threads for updating 
	// but could be very harmfull cause of shared memory 1 pipeline
	// main application thread should be empty
	while (true)
	{
		Sleep(2000);
		mModule->createTitle();// poggers... remove this later ;)
		mModule->ClearErrorLog();
	}
	printf("Closed...");
	system("pause");
}




