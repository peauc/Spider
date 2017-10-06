// LibUsing.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <thread>
#include "MyLib.hpp"

typedef int(__cdecl *f_dllfunc)(void);
typedef LRESULT(__cdecl *f_dllfunc2)(const int ncode, const WPARAM wparam, const LPARAM lparam);
HHOOK hook;
/*
int install(HINSTANCE hGetProcIDDLL)
{
	HOOKPROC proc = (HOOKPROC)GetProcAddress(hGetProcIDDLL, "CatchLLKeyboardProc");
	if (!proc)
	{
		std::cout << "could not locate the function"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (43);
	}
	hook = SetWindowsHookEx(WH_KEYBOARD_LL,proc, hGetProcIDDLL, 0);
	if (hook == NULL)
		return (-1);
	std::thread th(getmsg);
	th.join();
	//while (GetMessage(NULL, NULL, 0, 0));
	return (0);
}



int unistall()
{
	if (UnhookWindowsHookEx(hook) == 0)
		return (-1);
	return (0);
}*/
f_dllfunc unistall;

void getMessage()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

int suppr()
{
	std::cout << "Press a touch to unistall hook" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	getchar();
	//std::cin >> b;
	if (unistall() < 0)
	{
		std::cout << "Unistall hook : failed !" << std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (44);
	}
}

int main()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"KBHook.dll");
	int a, b;

	if (!hGetProcIDDLL)
	{
		std::cout << "Could not laod the dynamic library"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (42);
	}
	f_dllfunc install = (f_dllfunc)GetProcAddress(hGetProcIDDLL, "installHook");
	unistall = (f_dllfunc)GetProcAddress(hGetProcIDDLL, "unistallHook");
	if (!install || !unistall)
	{
		std::cout << "could not locate the function"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (43);
	}
	std::cout << "Press a touch to install hook" << std::endl;
	getchar();
	/*if (install() < 0)
	{
		std::cout << "Install hook : failed !" << std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		getchar();
		return (44);
	}*/
	//MSG msg;
	std::thread th1(install);
	std::thread th2(suppr);

	th1.join();
	th2.join();


	//th.join();
	return 0;
}

