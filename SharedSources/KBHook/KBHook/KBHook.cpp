// KBHook.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"

#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <iostream>

#include "KBHook.hh"

#pragma comment(lib, "user32.lib")

bool quit = false;

HHOOK hook{ NULL };

LRESULT CALLBACK KeyboardListener::CatchLLKeyboardProc(
	const int ncode, const WPARAM wparam, const LPARAM lparam
)
{
	KBDLLHOOKSTRUCT keyInfo = *((KBDLLHOOKSTRUCT*)lparam);
	
	if (wparam == WM_KEYDOWN)
	{
		/*std::ofstream file("key.txt", std::ofstream::out);
		if (!file.is_open())
			return (-1);
		file << keyInfo.vkCode;

		file.close();*/

		//std::cout << keyInfo.vkCode;

		MessageBox(NULL, L"Hello", L"YEs", NULL);
	}
	

	return CallNextHookEx(hook, ncode, wparam, lparam);

}

int KeyboardListener::getkey()
{
	while (!quit)
	{
		Sleep(100);
		int vk = 15;
		while (vk < 0xFC)
		{
			SHORT rv = GetAsyncKeyState(vk);
			if (rv & 0x100)
			{

				std::cout << "[KEYDOWN] =" << vk << std::endl;
			}
			++vk;
		}

	}
	return (0);
}

int KeyboardListener::installHook(DWORD threadId, HINSTANCE inst)
{

	hook = SetWindowsHookEx(WH_KEYBOARD_LL, CatchLLKeyboardProc, inst, threadId);
	std::cout << "ok" << std::endl;
	if (hook == NULL)
		return (-1);
	MSG msg;
	while (!quit && GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	/*while (!quit)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0) //Or use an if statement
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/

	return (0);
}
/*
int KeyboardListener::installHook()
{
	std::thread th(installHookThread);
	th.join();
	return (0);
}*/

int KeyboardListener::unistallHook()
{
	quit = true;
	if (UnhookWindowsHookEx(hook) == 0)
		return (-1);
	return (0);
}

extern "C" __declspec(dllexport) KeyboardListener *create()
{
	return (new KeyboardListener);
}

extern "C" __declspec(dllexport) void destroy(KeyboardListener *obj)
{
	delete obj;
}

void KeyboardListener::DoSomething()
{
	std::cout << "hello" << std::endl;
}