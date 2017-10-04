// LibUsing.cpp : Définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "MyLib.hpp"

typedef int(__cdecl *f_dllfunc2)(int, int);

int main()
{
	HINSTANCE hGetProcIDDLL = LoadLibrary(L"DisplayLib.dll");
	int a;

	if (!hGetProcIDDLL)
	{
		std::cout << "Could not laod the dynamic library"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		std::cin >> a;
		return (42);
	}
	f_dllfunc2 func = (f_dllfunc2)GetProcAddress(hGetProcIDDLL, "add");
	if (!func)
	{
		std::cout << "could not locate the function"
			<< std::endl;
		std::cout << "<Enter> to quit" << std::endl;
		std::cin >> a;
		return (43);
	}
	std::string txt = "Hello";
	std::cout << "Add : " << func(2, 15) << std::endl;
	std::cout << "<Enter> to quit" << std::endl;
	std::cin >> a;

	return 0;
}

